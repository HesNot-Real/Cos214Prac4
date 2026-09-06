#include "ZipCode.h"

Iterator* ZipCode::createIterator() {
	// TODO - implement ZipCode::createIterator
	throw "Not yet implemented";
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

ZipCode::~ZipCode() {
	for (auto parcel : parcels) {
		delete parcel;
	}
}
