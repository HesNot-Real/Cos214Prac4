#ifndef ITERATOR_H
#define ITERATOR_H

class Parcel;

class Iterator {


public:

	virtual void first() = 0;
	virtual Parcel* next() = 0;
	virtual Parcel* nextPriority() = 0;
	virtual bool isDone() = 0;
	virtual Parcel* currentItem() = 0;

	virtual ~Iterator() {}
};

#endif
