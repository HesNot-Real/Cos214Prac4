#ifndef PARCEL_H
#define PARCEL_H

class Parcel {


public:
	virtual boolean isPriority() = 0;

	virtual boolean isSigned() = 0;

	virtual boolean isFragile() = 0;

	virtual boolean isLarge() = 0;

	virtual string getCountry() = 0;

	virtual string getProvince() = 0;

	virtual string getCity() = 0;

	virtual string getZipCode() = 0;
};

#endif
