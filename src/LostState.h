#ifndef LOSTSTATE_H
#define LOSTSTATE_H

class LostState : ParcelState {


public:
	void advance(Parcel context);

	string getStatusName();
};

#endif
