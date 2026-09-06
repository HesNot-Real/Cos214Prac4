#ifndef AREACOMPONENT_H
#define AREACOMPONENT_H

#include <string>

#include "Parcel.h"
#include "RegionLevels.h"
class AreaComponent {

private:
	RegionLevel regionLevel;
	std::string regionName;

public:

	AreaComponent() = delete;
	AreaComponent(RegionLevel level, std::string name) :regionLevel(level), regionName(name) {};
	virtual void addComponent(AreaComponent* param) = 0;

	virtual void removeComponent(AreaComponent* param) = 0;

	virtual void addParcel(Parcel* parcel) = 0;

	virtual void removeParcel(Parcel* parcel) = 0;

	RegionLevel getLevel() const;

	std::string getName() const;

	virtual ~AreaComponent();
};

#endif
