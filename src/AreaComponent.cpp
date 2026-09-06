#include "AreaComponent.h"

RegionLevel AreaComponent::getLevel()const {
	return regionLevel;
}

std::string AreaComponent::getName()const {
	return regionName;
}

AreaComponent::~AreaComponent() {}
