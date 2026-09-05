#ifndef REGION_H
#define REGION_H

class Region : AreaComponent {

public:
	std::vector<AreaComponent> children;

	void addComponent(AreaComponent param);

	void remove(AreaComponent param);

	void addParcel(Parcel* parcel);

	void removeParcel(Parcel* parcel);
};

#endif
