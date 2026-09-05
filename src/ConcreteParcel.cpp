#include "ConcreteParcel.h"

std::map<std::string, std::string>& ConcreteParcel::getDetails() {
	// TODO - implement ConcreteParcel::getDetails
	throw "Not yet implemented";
}

boolean ConcreteParcel::isPriority() {
	// TODO - implement ConcreteParcel::isPriority
	throw "Not yet implemented";
}

boolean ConcreteParcel::isSigned() {
	// TODO - implement ConcreteParcel::isSigned
	throw "Not yet implemented";
}

boolean ConcreteParcel::isFragile() {
	// TODO - implement ConcreteParcel::isFragile
	throw "Not yet implemented";
}

boolean ConcreteParcel::isLarge() {
	// TODO - implement ConcreteParcel::isLarge
	throw "Not yet implemented";
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
