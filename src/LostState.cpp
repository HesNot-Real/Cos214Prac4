#include "LostState.h"
#include "Parcel.h"
#include <iostream>
using namespace std;

void LostState::advance(Parcel* context) {
	cout << "Invalid transition: parcel is lost and  cannot advance in delivery." << endl;
}

void LostState::reportLost(Parcel* context) {
	cout << "Parcel already Lost" << endl;
}

string LostState::getStatusName() {
	return "Lost";
}