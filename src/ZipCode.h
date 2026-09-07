#ifndef ZIPCODE_H
#define ZIPCODE_H

#include <vector>
#include <string>

#include "AreaComponent.h"
#include "Iterator.h"
#include "RegionLevels.h"

class ZipCode : public AreaComponent {

private:
	std::vector<Parcel*> parcels;
	std::string code;

public:

	ZipCode() = delete;
	ZipCode(std::string name) : AreaComponent(RegionLevel::ZipCode, name) {};
	Iterator* createIterator();

	void addParcel(Parcel* parcel);

	void removeParcel(Parcel* parcel);
	void addComponent(AreaComponent* param);
	void removeComponent(AreaComponent* param);
	void collectParcels(std::vector<Parcel*>& out) const;


	virtual ~ZipCode();
};

#endif
