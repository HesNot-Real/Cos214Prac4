#ifndef PARCEL_H
#define PARCEL_H

#include "ParcelState.h"
#include "RegionLevels.h"
#include <map>
#include <string>

class Parcel {

private:
	ParcelState state;

public:
	/// @brief Hold map of region level to its name. Levels include: Country, Province, City, ZipCode
	virtual std::map<RegionLevel, std::string>& getDetails() = 0;

	virtual bool isPriority() = 0;

	virtual bool isSigned() = 0;

	virtual bool isFragile() = 0;

	virtual bool isLarge() = 0;

	void advance();

	std::string getStatusName();
};

#endif
