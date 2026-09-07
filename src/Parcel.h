#ifndef PARCEL_H
#define PARCEL_H

#include <string>
#include <map>

class ParcelState;

class Parcel {

protected:
	ParcelState* state; //mo

public:

	Parcel();

	virtual bool isPriority() = 0;

	virtual bool isSigned() = 0;

	virtual bool isFragile() = 0;

	virtual bool isLarge() = 0;

	virtual std::string getCountry() = 0;

	virtual std::string getProvince() = 0;

	virtual std::string getCity() = 0;

	virtual std::string getZipCode() = 0;

	virtual std::string description() = 0;

	virtual ~Parcel();
	//mo for state
	void advance();
	void reportLost();
	std::string getStatusName();
	void setState(ParcelState* newState);
	virtual std::map<RegionLevel, std::string>& getDetails() = 0;



};

#endif
