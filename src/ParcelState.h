#ifndef PARCELSTATE_H
#define PARCELSTATE_H

#include <string>
using namespace std;

class Parcel; // check my forward declaration so no circular dependancy 

class ParcelState {

public:

	virtual void advance(Parcel* context) = 0;
	virtual void reportLost(Parcel* context) = 0;
	virtual string getStatusName() = 0;

	virtual bool isAwaitingPickup() { return false; }
	virtual bool isOnRoute() { return false; }
	virtual bool isSettled() { return false; }

    virtual ~ParcelState() {}
};

#endif