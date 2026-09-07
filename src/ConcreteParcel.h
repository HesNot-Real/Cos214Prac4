#ifndef CONCRETEPARCEL_H
#define CONCRETEPARCEL_H


#include <map>
#include <string>

#include "Parcel.h"
#include "RegionLevels.h"

class ConcreteParcel : public Parcel {
private:
	/// @brief Hold map of region level to its name. Levels include: Country, Province, City, ZipCode
	std::map<RegionLevel, std::string> addressDetails;
public:
	/// @brief Hold map of region level to its name. Levels include: Country, Province, City, ZipCode
	std::map<RegionLevel, std::string>& getDetails();
	std::string description() override;
	ConcreteParcel(std::map<RegionLevel, std::string> desc) : addressDetails(desc) {};

	bool isPriority();

	bool isSigned();

	bool isFragile();

	bool isLarge();


	virtual std::string getCountry();
	virtual std::string getProvince();
	virtual std::string getCity();
	virtual std::string getZipCode();
};

#endif
