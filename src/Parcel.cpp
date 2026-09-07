#include "Parcel.h"
#include "ParcelState.h"
#include "AwaitingPickupState.h"

Parcel::Parcel() {
	state = new AwaitingPickupState();
}

Parcel::~Parcel() {
	delete state;
}

void Parcel::advance() {
	state->advance(this);
}

void Parcel::reportLost() {
	state->reportLost(this);
}

string Parcel::getStatusName() {
	return state->getStatusName();
}

void Parcel::setState(ParcelState* newState) {
	if (state != nullptr) {

		delete state;
	}
	state = newState;
}

bool Parcel::isAwaitingPickup() { return state->isAwaitingPickup(); }
bool Parcel::isOnRoute() { return state->isOnRoute(); }
bool Parcel::isSettled() { return state->isSettled(); }