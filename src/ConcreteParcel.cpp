#include "ConcreteParcel.h"

ConcreteParcel::ConcreteParcel(std::map<RegionLevel, std::string> details) {
	addressDetails = details;
}

std::map<RegionLevel, std::string>& ConcreteParcel::getDetails() {
	return addressDetails; 
}

bool ConcreteParcel::isPriority() {
	return false;
}

bool ConcreteParcel::isSigned() {
	return false;
}

bool ConcreteParcel::isFragile() {
	return false;
}

bool ConcreteParcel::isLarge() {
	return false;
}

// string ConcreteParcel::getCountry() {
// 	return this->country;
// }

// string ConcreteParcel::getProvince() {
// 	return this->province;
// }

// string ConcreteParcel::getCity() {
// 	return this->city;
// }

// string ConcreteParcel::getZipCode() {
// 	return this->zipCode;
// }

string ConcreteParcel::description() {
	return "Standard parcel";
}
