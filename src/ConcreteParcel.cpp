#include "ConcreteParcel.h"

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

std::string ConcreteParcel::getCountry() {
	return this->addressDetails[RegionLevel::Country];
}

std::string ConcreteParcel::getProvince() {
	return this->addressDetails[RegionLevel::Province];

}

std::string ConcreteParcel::getCity() {
	return this->addressDetails[RegionLevel::City];

}

std::string ConcreteParcel::getZipCode() {
	return this->addressDetails[RegionLevel::ZipCode];

}

std::string ConcreteParcel::description() {
	return "Standard parcel";
}
