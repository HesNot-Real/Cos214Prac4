#ifndef ONROUTESTATE_H
#define ONROUTESTATE_H

#include "ParcelState.h"

class OnRouteState : public ParcelState {

public:
	void advance(Parcel* context);
	void reportLost(Parcel* context);
	string getStatusName();
	bool isOnRoute() override { return true; }
};

#endif