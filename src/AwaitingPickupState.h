#ifndef AWAITINGPICKUPSTATE_H
#define AWAITINGPICKUPSTATE_H

class AwaitingPickupState : ParcelState {


public:
	void advance(Parcel context);

	string getStatusName();
};

#endif
