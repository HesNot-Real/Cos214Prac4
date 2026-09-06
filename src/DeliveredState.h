#ifndef DELIVEREDSTATE_H
#define DELIVEREDSTATE_H

#include "ParcelState.h"

class DeliveredState : public ParcelState {

public:
	void advance(Parcel* context);
	void reportLost(Parcel* context);
	string getStatusName();
};

#endif