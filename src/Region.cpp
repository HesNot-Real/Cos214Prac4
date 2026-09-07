#include "Region.h"
#include "ParcelIterator.h"

void Region::addComponent(AreaComponent* param) {


	std::vector<AreaComponent*>::iterator it = children.begin();
	for (;it != children.end();it++) {
		if (*it == param) {
			return;
		}
	}
	children.push_back(param);
}

void Region::removeComponent(AreaComponent* param) {
	std::vector<AreaComponent*>::iterator it = children.begin();
	for (;it != children.end();it++) {
		if (*it == param) {
			children.erase(it);
			return;
		}
	}
}

void Region::addParcel(Parcel* parcel) {
	auto details = parcel->getDetails();

	std::vector<AreaComponent*>::iterator it = children.begin();
	for (;it != children.end();it++) {
		if (details[(*it)->getLevel()] == (*it)->getName()) {
			(*it)->addParcel(parcel);
			return;
		}
	}

}

void Region::removeParcel(Parcel* parcel) {
	auto details = parcel->getDetails();

	std::vector<AreaComponent*>::iterator it = children.begin();
	for (;it != children.end();it++) {
		if (details[(*it)->getLevel()] == (*it)->getName()) {
			(*it)->removeParcel(parcel);
			return;
		}
	}
}

Region::~Region() {
	for (auto child : children) {
		delete child;
	}
}


//trying something 

// recursively walks every child, letting each level add its own parcels, without ever exposing children
void Region::collectParcels(std::vector<Parcel*>& out) const {
	for (auto child : children) {
		child->collectParcels(out);
	}
}

//  to flattens the whole subtree into one snapshot and wrap it in a ParcelIterator
Iterator* Region::createIterator() {
	std::vector<Parcel*> all;
	collectParcels(all);
	return new ParcelIterator(all);
}