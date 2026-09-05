#ifndef CONCRETEPARCEL_H
#define CONCRETEPARCEL_H

class ConcreteParcel : Parcel {

private:
	string country;
	string province;
	string city;
	string zipCode;

public:
	std::map<std::string, std::string>& getDetails();

	boolean isPriority();

	boolean isSigned();

	boolean isFragile();

	boolean isLarge();

	string getCountry();

	string getProvince();

	string getCity();

	string getZipCode();
};

#endif
