#ifndef CONCRETEPARCEL_H
#define CONCRETEPARCEL_H

#include <map>
#include <string>

#include "Parcel.h"
#include "RegionLevels.h"

class ConcreteParcel : public Parcel {
private:
	std::map<RegionLevel, std::string> addressDetails;
	std::string label;
public:
	std::map<RegionLevel, std::string>& getDetails();

	ConcreteParcel(std::map<RegionLevel, std::string> details, std::string label);
	std::string description() override;

	bool isPriority();
	bool isSigned();
	bool isFragile();
	bool isLarge();
	std::string getLabel() override;
};

#endif