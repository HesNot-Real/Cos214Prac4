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

//-------- network setup --------
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

//-------- ------------------------display helprs ------------------------
void printAddress(Parcel* p) {
	map<RegionLevel, string> details = p->getDetails();
	cout << "      route: " << details[RegionLevel::Country] << " > "
	     << details[RegionLevel::Province] << " > "
	     << details[RegionLevel::City] << " > "
	     << details[RegionLevel::ZipCode] << endl;
}

string tags(Parcel* p) {
	string result = "";
	if (p->isPriority()) result += "[Priority]";
	if (p->isFragile())  result += "[Fragile]";
	if (p->isSigned())   result += "[Signed]";
	if (p->isLarge())    result += "[Large]";
	return result.empty() ? "[Standard]" : result;
}

void printLine(string label, Parcel* p) {
	cout << "  " << label << " " << tags(p) << " - " << p->getStatusName() << endl;
}

//-------- section 1 composite structure --------
void CompositeStructure(DeliveryNetwork& net) {
	cout << "\n===== 1. Composite Structure =====" << endl;
	cout << "Network: South Africa > Gauteng > Pretoria > {0181, 0083}" << endl;
	cout << "Invalid operation  Attempting to put a Region inside a ZipCode:" << endl;
	net.zip0083->addComponent(net.zip0083); // rejected
}

//-------------------- 2 - parcel lifecycle walkthrough --------------------------------------

void LifecycleWalkthrough(Parcel* p, string label) {
	cout << "\n========== 2. Parcel Lifecycle Walkthrough: " << label << " ============" << endl;
	cout << "  status: " << p->getStatusName() << endl;

	cout << " parcel advanced" << endl;
	p->advance();
	cout << "  status: " << p->getStatusName() << endl;

	cout << "parcel advanced" << endl;
	p->advance();
	cout << "  status: " << p->getStatusName() << endl;

	cout << "  parcel advanced again (invalid, already delivered):" << endl;
	p->advance();
	cout << "  status: " << p->getStatusName() << endl;
}

//-------- section 3: lost in transit-----------------------------------------------------------

void LostBranch(Parcel* p, string label) {
	cout << "\n======== 3.  Parcel lost in transit (" << label << ") =======" << endl;
	cout << "  status: " << p->getStatusName() << endl;
	cout << "  parcel advanced (AwaitingPickup -> OnRoute)" << endl;
	p->advance();
	cout << "  status: " << p->getStatusName() << endl;
	cout << "  parcel reported lost" << endl;
	p->reportLost();
	cout << "  status: " << p->getStatusName() << endl;
	cout << "  sill mistake, parcel reported lost again :" << endl;
	p->reportLost();
}

//-------- section 4: decorator stacking --------
void DecoratorStack(Parcel* p, string label) {
	cout << "\n====== 4. Decorator: Stacked responsibilities (" << label << ") ==========" << endl;
	printLine(label, p);
	cout << "  Full description: " << p->description() << endl;
}

//------------- section 5: iterators two traversals -------------------------------
void Iterators(DeliveryNetwork& net) {
	cout << "\n===== 5. Iterator: Full Sweep vs Priority Only =====" << endl;

	Iterator* fullSweep = net.country->createIterator();
	cout << "Full sweep (every parcel in the network):" << endl;
	fullSweep->first();
	while (!fullSweep->isDone()) {
		Parcel* item = fullSweep->currentItem();
		printLine(item->getLabel(), item); 
		fullSweep->next();
	}
	delete fullSweep;

	Iterator* priorityOnly = net.country->createIterator();
	cout << "Priority only:" << endl;
	priorityOnly->first();
	if (!priorityOnly->isDone() && !priorityOnly->currentItem()->isPriority()) {
		priorityOnly->nextPriority();
	}
	while (!priorityOnly->isDone()) {
		Parcel* item = priorityOnly->currentItem();
		printLine(item->getLabel(), item);
		priorityOnly->nextPriority();
	}
	delete priorityOnly;
}

//-------- section 6: dispatch and delivery, with signing --------
void DispatchAndDelivery(DeliveryNetwork& net) {
	cout << "\n===== 6. Full Route: Pickup -> Delivery -> Signing =====" << endl;

	cout << "-- Pickup wave (full sweep) --" << endl;
	Iterator* pickup = net.country->createIterator();
	pickup->first();
	while (!pickup->isDone()) {
		Parcel* item = pickup->currentItem();
		if (item->isAwaitingPickup()) {
			cout << "  " << item->getLabel() << ": picked up, now on route." << endl;
			item->advance();
		}
		pickup->next();
	}
	delete pickup;

	cout << "-- Delivery wave (priority order) --" << endl;
	Iterator* deliveryPriority = net.country->createIterator();
	deliveryPriority->first();
	if (!deliveryPriority->isDone() && !deliveryPriority->currentItem()->isPriority()) {
		deliveryPriority->nextPriority();
	}
	while (!deliveryPriority->isDone()) {
		Parcel* item = deliveryPriority->currentItem();
		if (item->isOnRoute()) {
			item->advance();
			cout << "  " << item->getLabel() << ": delivered (priority).";
			if (item->isSigned()) {
				cout << " Recipient signature collected.";
			}
			cout << endl;
		}
		deliveryPriority->nextPriority();
	}
	delete deliveryPriority;

	Iterator* deliveryRest = net.country->createIterator();
	deliveryRest->first();
	while (!deliveryRest->isDone()) {
		Parcel* item = deliveryRest->currentItem();
		if (item->isOnRoute()) {
			item->advance();
			cout << "  " << item->getLabel() << ": delivered.";
			if (item->isSigned()) {
				cout << " Recipient signature collected.";
			}
			cout << endl;
		}
		deliveryRest->next();
	}
	delete deliveryRest;

	cout << "-- Already settled --" << endl;
	Iterator* settled = net.country->createIterator();
	settled->first();
	while (!settled->isDone()) {
		Parcel* item = settled->currentItem();
		if (item->isSettled()) { 
			cout << "  " << item->getLabel() << ": " << item->getStatusName() << " (from earlier)." << endl;
		}
		settled->next();
	}
	delete settled;
}

//-------- section 7/8: structural changes and snapshot-----------------------------
void StructuralChanges(DeliveryNetwork& net, Parcel* misrouted, string misroutedLabel) {
	cout << "\n===== 7. Structural Change: Reroute =====" << endl;
	cout << "  " << misroutedLabel << " misrouted, moving 0083 -> 0181" << endl;
	net.zip0083->removeParcel(misrouted);
	net.zip0181->addParcel(misrouted);

	cout << "\n===== 8. Structural Change: Archive After Delivery =====" << endl;
	Iterator* beforeArchive = net.zip0181->createIterator(); // snapshot taken now

	Iterator* scan = net.zip0181->createIterator();
	scan->first();
	Parcel* toArchive = nullptr;
	while (!scan->isDone()) {
		if (scan->currentItem()->getStatusName() == "Delivered") {
			toArchive = scan->currentItem();
			break;
		}
		scan->next();
	}
	delete scan;

	if (toArchive != nullptr) {
		cout << "  found " << toArchive->getLabel() << " (Delivered) in 0181 - archiving it out." << endl;
		net.zip0181->removeParcel(toArchive);
	} else {
		cout << "  no delivered parcel found in 0181 to archive." << endl;
	}

	cout << "  snapshot iterator (created BEFORE the archive) still sees:" << endl;
	beforeArchive->first();
	while (!beforeArchive->isDone()) {
		printLine(beforeArchive->currentItem()->getLabel(), beforeArchive->currentItem());
		beforeArchive->next();
	}
	delete beforeArchive;

	cout << "  fresh iterator (created AFTER the archive) sees:" << endl;
	Iterator* afterArchive = net.zip0181->createIterator();
	afterArchive->first();
	while (!afterArchive->isDone()) {
		printLine(afterArchive->currentItem()->getLabel(), afterArchive->currentItem());
		afterArchive->next();
	}
	delete afterArchive;

	if (toArchive != nullptr) {
		delete toArchive;
	}
}

//-------- section 9: intake rejection --------
void OversizedRejection(DeliveryNetwork& net) {
	cout << "\n===== 9. Intake Rejection: Oversized Parcel =====" << endl;
	Parcel* oversized = new LargeParcel(new ConcreteParcel({
		{RegionLevel::Country, "South Africa"}, {RegionLevel::Province, "Gauteng"},
		{RegionLevel::City, "Pretoria"}, {RegionLevel::ZipCode, "0083"}
	}, "Wardrobe"));

	if (oversized->isLarge()) {
		cout << "  Wardrobe requires chunky truck, rejected from standard courier route." << endl;
		delete oversized;
	} else {
		net.zip0083->addParcel(oversized);
	}
}

int main() {
	cout << "===== TaskForge: Regional Courier Dispatch =====" << endl;

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
	ConcreteParcel* p2 = new ConcreteParcel(addr0083, "Order #4502");
	ConcreteParcel* p3 = new ConcreteParcel(addr0181, "Order #4519");
	Parcel* priorityParcel = new PriorityParcel(new FragileParcel(new SignedParcel(
		new ConcreteParcel(addr0083, "Antique Vase"))));
	Parcel* signedOnly = new SignedParcel(new ConcreteParcel(addr0181, "Order #4530"));

	net.country->addParcel(p1);
	net.country->addParcel(p2);
	net.country->addParcel(p3);
	net.country->addParcel(priorityParcel);
	net.country->addParcel(signedOnly);

	CompositeStructure(net);
	LifecycleWalkthrough(p1, "Order #4471");
	LostBranch(p3, "Order #4519");
	DecoratorStack(priorityParcel, "Antique Vase");
	Iterators(net);
	DispatchAndDelivery(net);       // advances remaining parcels, signs where needed
	StructuralChanges(net, p2, "Order #4502");
	OversizedRejection(net);

	cout << "\n===== Done - clean up =====" << endl;

	delete net.country; // cascades
	return 0;
}