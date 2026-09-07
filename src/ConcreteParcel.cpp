#include "ConcreteParcel.h"

std::map<RegionLevel, std::string>& ConcreteParcel::getDetails() {
	// TODO - implement ConcreteParcel::getDetails
	throw "Not yet implemented";
}

bool ConcreteParcel::isPriority() {
	// TODO - implement ConcreteParcel::isPriority
	return false;
}

bool ConcreteParcel::isSigned() {
	// TODO - implement ConcreteParcel::isSigned
	return false;
}

bool ConcreteParcel::isFragile() {
	// TODO - implement ConcreteParcel::isFragile
	return false;
}

bool ConcreteParcel::isLarge() {
	// TODO - implement ConcreteParcel::isLarge
	return false;
}

string ConcreteParcel::getCountry() {
	return this->country;
}

string ConcreteParcel::getProvince() {
	return this->province;
}

string ConcreteParcel::getCity() {
	return this->city;
}

string ConcreteParcel::getZipCode() {
	return this->zipCode;
}

string ConcreteParcel::description() {
	return "Standard parcel";
}
