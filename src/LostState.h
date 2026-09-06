#ifndef LOSTSTATE_H
#define LOSTSTATE_H

#include "ParcelState.h"

class LostState : public ParcelState {

public:
	void advance(Parcel* context);
	void reportLost(Parcel* context);
	string getStatusName();
};

#endif