#include "AwaitingPickupState.h"
#include "Parcel.h"
#include "OnRouteState.h"
#include <iostream>
using namespace std;

void AwaitingPickupState::advance(Parcel* context) {
	context->setState(new OnRouteState());
}

void AwaitingPickupState::reportLost(Parcel* context) {
	cout << "Invalid transition: cannot report a parcel as lost before it has been picked up silly." << endl;
}

string AwaitingPickupState::getStatusName() {
	return "Awaiting Pickup";
}