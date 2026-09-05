#ifndef AREACOMPONENT_H
#define AREACOMPONENT_H

class AreaComponent {

private:
	string regionLevel;
	string regionName;

public:
	virtual void addComponent(AreaComponent param) = 0;

	virtual void remove(AreaComponent param) = 0;

	virtual void addParcel(Parcel* parcel) = 0;

	virtual void removeParcel(Parcel* parcel) = 0;

	string getLevel();

	string getName();
};

#endif
