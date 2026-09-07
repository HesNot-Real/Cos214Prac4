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

int main() {

	//-------- building the delivery hierarchy (composite) --------
	Region* country = new Region(RegionLevel::Country, "South Africa");
	Region* province = new Region(RegionLevel::Province, "Gauteng");
	Region* city = new Region(RegionLevel::City, "Pretoria");
	ZipCode* zip0181 = new ZipCode("0181");
	ZipCode* zip0083 = new ZipCode("0083");

	country->addComponent(province);
	province->addComponent(city);
	city->addComponent(zip0181);
	city->addComponent(zip0083);

	//-------- composite invalid operation since a ZipCode cannot hold regions --------
	zip0181->addComponent(city);

	//-------- parcels for zip 0181 --------
	map<RegionLevel, string> addr0181 = {
		{RegionLevel::Country, "South Africa"},
		{RegionLevel::Province, "Gauteng"},
		{RegionLevel::City, "Pretoria"},
		{RegionLevel::ZipCode, "0181"}
	};
	ConcreteParcel* p1 = new ConcreteParcel(addr0181);
	ConcreteParcel* p2 = new ConcreteParcel(addr0181);

	//-------- parcels for zip 0083, one wrapped in stacked decorators --------
	map<RegionLevel, string> addr0083 = {
		{RegionLevel::Country, "South Africa"},
		{RegionLevel::Province, "Gauteng"},
		{RegionLevel::City, "Pretoria"},
		{RegionLevel::ZipCode, "0083"}
	};
	ConcreteParcel* p3 = new ConcreteParcel(addr0083);
	Parcel* p4 = new PriorityParcel(new FragileParcel(new SignedParcel(new ConcreteParcel(addr0083))));

	country->addParcel(p1);
	country->addParcel(p2);
	country->addParcel(p3);
	country->addParcel(p4);

	//----------------------- stacked responsibilities --------
	cout << "-------- Decorator - stacked responsibilities --------" << endl;
	cout << p4->description() << endl;
	cout << "priority=" << p4->isPriority() << " fragile=" << p4->isFragile()
	     << " signed=" << p4->isSigned() << " large=" << p4->isLarge() << endl;


	//------- valid lifecycle --
	cout << "\n-------- State: p1 valid lifecycle --------" << endl;
	cout << "p1: " << p1->getStatusName() << endl;
	p1->advance();
	cout << "p1: " << p1->getStatusName() << endl;
	p1->advance();
	cout << "p1: " << p1->getStatusName() << endl;

	//-------- state- invalid transition on a delivered parcel --------
	cout << "\n-------- State with invalid transition --------" << endl;
	p1->advance();

	//-------- state - alternate branch, parcel lost in transit --------
	cout << "\n-------- State with alternate branch (lost) --------" << endl;
	p2->advance();
	p2->reportLost();
	cout << "p2: " << p2->getStatusName() << endl;
	p2->advance();

	//-------- Iterator: two independent traversals over the same structure --------
	cout << "\n-------- Iterator: full sweep vs priorit --------" << endl;
	Iterator* fullSweep = country->createIterator();
	Iterator* priorityOnly = country->createIterator();

	fullSweep->first();
	cout << "Full sweep: ";
	while (!fullSweep->isDone()) {
		cout << fullSweep->currentItem()->getStatusName() << " | ";
		fullSweep->next();
	}
	cout << endl;

	priorityOnly->first();
	if (!priorityOnly->isDone() && !priorityOnly->currentItem()->isPriority()) {
		priorityOnly->nextPriority();
	}
	cout << "Priority only: ";
	while (!priorityOnly->isDone()) {
		cout << priorityOnly->currentItem()->description() << " | ";
		priorityOnly->nextPriority();
	}
	cout << endl;

	delete fullSweep;
	delete priorityOnly;

	//-------- task 3, Scenario 1-  dispatchers full day report --------
	cout << "\n-------- Scenario 1: dispatcher full day report --------" << endl;
	Iterator* dispatcherView = country->createIterator();
	dispatcherView->first();
	while (!dispatcherView->isDone()) {
		Parcel* current = dispatcherView->currentItem();
		cout << current->description() << " [" << current->getStatusName() << "]" << endl;
		current->advance();
		dispatcherView->next();
	}
	delete dispatcherView;

	//-------- task 3, Scenario 2: delivery and structural change --------
	cout << "\n-------- Scenario 2: delivery + structural change --------" << endl;
	p3->advance(); // p3 was already OnRoute after Scenario 1's dispatcher pass this delivers it

	Iterator* beforeRemoval = zip0083->createIterator(); // snapshot taken while p3 is still active
	zip0083->removeParcel(p3); // structural change: p3 leaves the active composite

	cout << "Snapshot iterator (created before removal) still sees: ";
	beforeRemoval->first();
	while (!beforeRemoval->isDone()) {
		cout << beforeRemoval->currentItem()->getStatusName() << " | ";
		beforeRemoval->next();
	}
	cout << endl;
	delete beforeRemoval;

	Iterator* afterRemoval = zip0083->createIterator(); // new snapshot, taken after removal
	int remaining = 0;
	afterRemoval->first();
	while (!afterRemoval->isDone()) { remaining++; afterRemoval->next(); }
	cout << "New iterator (created after removal) sees " << remaining << " parcels left in zip 0083." << endl;
	delete afterRemoval;

	delete p3; // no longer owned by the composite, so we have to have main must clean it up

	//-------- Cleanup --------
	delete country;
	return 0;
}