#ifndef AWAITINGPICKUPSTATE_H
#define AWAITINGPICKUPSTATE_H

#include "ParcelState.h"

class AwaitingPickupState : public ParcelState {

public:
	void advance(Parcel* context);
	void reportLost(Parcel* context);
	string getStatusName();
};

#endif