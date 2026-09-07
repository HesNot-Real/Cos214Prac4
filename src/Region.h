#ifndef REGION_H
#define REGION_H

#include <vector>
#include "AreaComponent.h"
#include "RegionLevels.h"

class Region : public AreaComponent {
	private:
		std::vector<AreaComponent*> children; //rule 7
public:
	Region() = delete;
	Region(RegionLevel level, std::string name) :AreaComponent(level, name) {};

	void addComponent(AreaComponent* param);
	void removeComponent(AreaComponent* param);
	void addParcel(Parcel* parcel);
	void removeParcel(Parcel* parcel);

	Iterator* createIterator(); //
	void collectParcels(std::vector<Parcel*>& out) const;

	virtual ~Region();
};

#endif
