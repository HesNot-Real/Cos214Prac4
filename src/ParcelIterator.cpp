#include "ParcelState.h"
#include "ParcelIterator.h"
#include "Parcel.h"
using namespace std;


ParcelIterator::ParcelIterator(vector<Parcel*> parcelList) {
	items = parcelList;
	index = 0;
}

void ParcelIterator::first() {
	index = 0;
}

void ParcelIterator::next() {
	if (index < (int)items.size()) {
		index++;
	}
}

void ParcelIterator::nextPriority() {

	index++;
	while (index < (int)items.size() && !items[index]->isPriority()) {
		index++;
	}
}

bool ParcelIterator::isDone() {
	return index >= (int)items.size();
}

Parcel* ParcelIterator::currentItem() {
	if (isDone()) {
		return nullptr;
	}
	return items[index];
}

ParcelIterator::~ParcelIterator() {
	// ownership
}