#ifndef DELIVEREDSTATE_H
#define DELIVEREDSTATE_H

class DeliveredState : ParcelState {


public:
	void advance(Parcel context);

	string getStatusName();
};

#endif
