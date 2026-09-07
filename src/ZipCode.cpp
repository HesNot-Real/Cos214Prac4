#include "ZipCode.h"
#include "ParcelIterator.h"

Iterator* ZipCode::createIterator() {
	return new ParcelIterator(parcels);
}

void ZipCode::addParcel(Parcel* parcel) {
	for (auto it = parcels.begin();it != parcels.end();it++) {
		if (*it == parcel) {
			return;
		}
	}
	parcels.push_back(parcel);
}

void ZipCode::removeParcel(Parcel* parcel) {
	for (auto it = parcels.begin();it != parcels.end();it++) {
		if (*it == parcel) {
			parcels.erase(it);
			return;
		}
	}
}

void ZipCode::addComponent(AreaComponent* param) {
	std::cout << "inval a ZipCode cannot contain nested regions" << std::endl;
}

void ZipCode::removeComponent(AreaComponent* param) {
	std::cout << "Invalid a ZipCode cannot contain nested regions" << std::endl;
}

void ZipCode::collectParcels(std::vector<Parcel*>& out) const {

	out.insert(out.end(), parcels.begin(), parcels.end());
	
}

ZipCode::~ZipCode() {
	for (auto parcel : parcels) {
		delete parcel;
	}
}
