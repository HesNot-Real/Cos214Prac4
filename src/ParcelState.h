#ifndef PARCELSTATE_H
#define PARCELSTATE_H

class ParcelState {


public:
	void advance(Parcel context);

	string getStatusName();

	void ~ParcelState();
};

#endif
