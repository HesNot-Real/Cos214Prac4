#ifndef REGION_H
#define REGION_H

#include <vector>
#include "AreaComponent.h"
#include "RegionLevels.h"

class Region : public AreaComponent {

public:
	Region() = delete;
	Region(RegionLevel level, std::string name) :AreaComponent(level, name) {};
	std::vector<AreaComponent*> children;

	void addComponent(AreaComponent* param);

	void removeComponent(AreaComponent* param);

	void addParcel(Parcel* parcel);

	void removeParcel(Parcel* parcel);

	virtual ~Region();
};

#endif
