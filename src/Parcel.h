#ifndef PARCEL_H
#define PARCEL_H

#include <string>
#include <map>
#include "RegionLevels.h"
using namespace std;

class ParcelState;

class Parcel {

protected:
	ParcelState* state; //mo

public:

	Parcel();

	virtual bool isPriority() = 0;

	virtual bool isSigned() = 0;

	virtual bool isFragile() = 0;

	virtual bool isLarge() = 0;

	// virtual string getCountry() = 0;

	// virtual string getProvince() = 0;

	// virtual string getCity() = 0;

	// virtual string getZipCode() = 0;

	virtual std::string description() = 0;

	virtual ~Parcel();
	//mo for state
	virtual void advance();
	virtual void reportLost();
	virtual string getStatusName();
	virtual void setState(ParcelState* newState);
//mo2
	virtual bool isAwaitingPickup();
	virtual bool isOnRoute();
	virtual bool isSettled();
	
	virtual map<RegionLevel, string>& getDetails() = 0;
	virtual string getLabel() = 0;


};

#endif
