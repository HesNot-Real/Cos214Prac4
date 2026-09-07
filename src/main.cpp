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

	//-------- Composite: build the delivery hierarchy --------
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
	cout << "-------- Decorator: stacked responsibilities --------" << endl;
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
	cout << "\n-------- State: invalid transition --------" << endl;
	p1->advance();

	//-------- state - alternate branch, parcel lost in transit --------
	cout << "\n-------- State: alternate branch (lost) --------" << endl;
	p2->advance();
	p2->reportLost();
	cout << "p2: " << p2->getStatusName() << endl;
	p2->advance();

	