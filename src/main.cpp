#include <iostream>
#include <map>
#include <string>

#include "Region.h"
#include "ZipCode.h"
#include "ConcreteParcel.h"
#include "ParcelDecorator.h"
#include "Iterator.h"
#include "RegionLevels.h"

using namespace std;

//--------------------------------------------- network setup --------
struct DeliveryNetwork {
	Region* country;
	ZipCode* zip0181;
	ZipCode* zip0083;
};

DeliveryNetwork buildNetwork() {
	Region* country = new Region(RegionLevel::Country, "South Africa");
	Region* province = new Region(RegionLevel::Province, "Gauteng");
	Region* city = new Region(RegionLevel::City, "Pretoria");
	ZipCode* zip0181 = new ZipCode("0181");
	ZipCode* zip0083 = new ZipCode("0083");

	country->addComponent(province);
	province->addComponent(city);
	city->addComponent(zip0181);
	city->addComponent(zip0083);

	return DeliveryNetwork{country, zip0181, zip0083};
}

//-------- Thanks for the suggestion Jamie --------

void printAddress(Parcel* p) {
	map<RegionLevel, string> details = p->getDetails();
	cout << "    " << details[RegionLevel::Country] << " > "
	     << details[RegionLevel::Province] << " > "
	     << details[RegionLevel::City] << " > "
	     << details[RegionLevel::ZipCode] << endl;
}

//-------- scenario 1: morning dispatch ------------------------------------------------------------

void runMorningDispatch(DeliveryNetwork& net) {
	cout << "-------- Morning Dispatch --------" << endl;

	Iterator* manifest = net.country->createIterator();
	cout << "Manifest:" << endl;
	manifest->first();
	while (!manifest->isDone()) {
		Parcel* item = manifest->currentItem();
		cout << "  " << item->description() << " [" << item->getStatusName() << "]" << endl;
		printAddress(item);
		manifest->next();
	}
	delete manifest;

	Iterator* priorityQueue = net.country->createIterator();
	cout << "Priority load order:" << endl;
	priorityQueue->first();
	if (!priorityQueue->isDone() && !priorityQueue->currentItem()->isPriority()) {
		priorityQueue->nextPriority();
	}
	while (!priorityQueue->isDone()) {
		cout << "  " << priorityQueue->currentItem()->description() << endl;
		priorityQueue->nextPriority();
	}
	delete priorityQueue;

	cout << "Trucks depart." << endl;
	Iterator* departure = net.country->createIterator();
	departure->first();
	while (!departure->isDone()) {
		departure->currentItem()->advance(); // AwaitingPickup -> OnRoute
		departure->next();
	}
	delete departure;
}

//-------- scenario 2: afternoon incident --------
// (reroute and removeParcel as two distinct structural changes



void runAfternoonIncident(DeliveryNetwork& net, Parcel* priorityParcel, Parcel* standardParcel) {
	cout << "\n-------- Afternoon Incident --------" << endl;

	cout << "Parcel misrouted, moving to correct zip code:" << endl;
	net.zip0083->removeParcel(standardParcel);
	net.zip0181->addParcel(standardParcel);
	cout << "  " << standardParcel->description() << " now routed via 0181" << endl;

	Iterator* endOfDayReport = net.zip0083->createIterator(); // snapshot taken 

	cout << "Courier delivers: " << priorityParcel->description() << endl;
	priorityParcel->advance(); // OnRoute -Delivered

	cout << "the bru accidentally rescans it: ";
	priorityParcel->advance();

	cout << "driver can't locate a parcel in 0181:" << endl;
	standardParcel->reportLost(); // OnRoute -> Lost (alternate branch)
	cout << "  " << standardParcel->description() << " status: " << standardParcel->getStatusName() << endl;

	//structural change 2    delivered parcel archived out
	cout << "Delivered parcel is archived out of the active zip code." << endl;
	net.zip0083->removeParcel(priorityParcel); // main now owns it DELETE MO

	cout << "Supervisor's report (snapshot taken before the archive):" << endl;
	endOfDayReport->first();
	while (!endOfDayReport->isDone()) {
		Parcel* item = endOfDayReport->currentItem();
		cout << "  " << item->description() << " [" << item->getStatusName() << "]" << endl;
		endOfDayReport->next();
	}
	delete endOfDayReport;

	cout << "Live view (fresh iterator, created after the archive):" << endl;
	Iterator* freshView = net.zip0083->createIterator();
	freshView->first();
	while (!freshView->isDone()) {
		Parcel* item = freshView->currentItem();
		cout << "  " << item->description() << " [" << item->getStatusName() << "]" << endl;
		freshView->next();
	}
	delete freshView;

	// oversized parcel rejected before it even enters the network 
	cout << "\nNew intake: an oversized item arrives." << endl;
	Parcel* oversized = new LargeParcel(new ConcreteParcel({
		{RegionLevel::Country, "South Africa"}, {RegionLevel::Province, "Gauteng"},
		{RegionLevel::City, "Pretoria"}, {RegionLevel::ZipCode, "0083"}
	}, "Wardrobe"));

	if (oversized->isLarge()) {
		cout << "  " << oversized->description() << " requires special freight, not standard courier route." << endl;
		delete oversized; // rejected and dont join comp
	} else {
		net.zip0083->addParcel(oversized);
	}
}

int main() {
	cout << "======= TaskForge: Regional Courier Dispatch ======" << endl;
	cout << "Tracking parcels across South Africa > Gauteng > Pretoria\n" << endl;

	DeliveryNetwork net = buildNetwork();

	map<RegionLevel, string> addr0181 = {
		{RegionLevel::Country, "South Africa"}, {RegionLevel::Province, "Gauteng"},
		{RegionLevel::City, "Pretoria"}, {RegionLevel::ZipCode, "0181"}
	};
	map<RegionLevel, string> addr0083 = {
		{RegionLevel::Country, "South Africa"}, {RegionLevel::Province, "Gauteng"},
		{RegionLevel::City, "Pretoria"}, {RegionLevel::ZipCode, "0083"}
	};

	ConcreteParcel* p1 = new ConcreteParcel(addr0181, "Order #4471");
	Parcel* priorityParcel = new PriorityParcel(new FragileParcel(new SignedParcel(
		new ConcreteParcel(addr0083, "Antique Vase"))));
	ConcreteParcel* p3 = new ConcreteParcel(addr0083, "Order #4502");

	net.country->addParcel(p1);
	net.country->addParcel(priorityParcel);
	net.country->addParcel(p3);

	runMorningDispatch(net);
	runAfternoonIncident(net, priorityParcel, p3);

	delete priorityParcel; // removed from the composite, so main must free it
	delete net.country;    // cascades
	return 0;
}