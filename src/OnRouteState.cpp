#include "OnRouteState.h"
#include "Parcel.h"
#include "DeliveredState.h"
#include "LostState.h"
#include <iostream>
using namespace std;

void OnRouteState::advance(Parcel* context) {
	context->setState(new DeliveredState());
}

void OnRouteState::reportLost(Parcel* context) {
	context->setState(new LostState());
}

string OnRouteState::getStatusName() {
	return "On Route";
}