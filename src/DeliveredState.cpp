#include "DeliveredState.h"
#include "Parcel.h"
#include <iostream>
using namespace std;

void DeliveredState::advance(Parcel* context) {
	cout << "Parcel has already been delivered." << endl;
}

void DeliveredState::reportLost(Parcel* context) {
	cout << "Invalid transition: cannot report a delivered parcel as lost." << endl;
}

string DeliveredState::getStatusName() {
	return "Delivered";
}