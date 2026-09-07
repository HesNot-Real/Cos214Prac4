#ifndef PARCELITERATOR_H
#define PARCELITERATOR_H

#include <vector>
#include "Iterator.h"
using namespace std;

class ParcelIterator : public Iterator {
	private:
		vector<Parcel*> items; // need this for the snapshot
		int index;

	public:
		ParcelIterator() = delete;
		ParcelIterator(vector<Parcel*> parcelList);


		void first();
		void next();
		void nextPriority();
		bool isDone();
		Parcel* currentItem();

		virtual ~ParcelIterator();
};

#endif
