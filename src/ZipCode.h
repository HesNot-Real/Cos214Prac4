#ifndef ZIPCODE_H
#define ZIPCODE_H

class ZipCode : AreaComponent, Aggregate {

private:
	std::vector<Parcel> parcels;
	string code;

public:
	Iterator* createIterator();

	void addParcel(Parcel* parcel);

	void removeParcel(Parcel* parcel);
};

#endif
