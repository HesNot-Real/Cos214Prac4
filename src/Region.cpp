#include "Region.h"

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
