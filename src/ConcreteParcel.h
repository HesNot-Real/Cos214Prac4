#ifndef CONCRETEPARCEL_H
#define CONCRETEPARCEL_H


#include <map>
#include <string>

#include "Parcel.h"

class ConcreteParcel : public Parcel {
private:
	/// @brief Hold map of region level to its name. Levels include: Country, Province, City, ZipCode
	std::map<RegionLevel, std::string> addressDetails;
public:
	/// @brief Hold map of region level to its name. Levels include: Country, Province, City, ZipCode
	std::map<RegionLevel, std::string>& getDetails();

	bool isPriority();

	bool isSigned();

	bool isFragile();

	bool isLarge();
};

#endif
