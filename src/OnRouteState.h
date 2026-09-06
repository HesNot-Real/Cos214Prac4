#ifndef ONROUTESTATE_H
#define ONROUTESTATE_H

class OnRouteState : ParcelState {


public:
	void advance(Parcel context);

	string getStatusName();
};

#endif
