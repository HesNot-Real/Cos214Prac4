#ifndef DECORATOR_H
#define DECORATOR_H

#include "Parcel.h"
#include <string>

class ParcelDecorator : public Parcel {
	private:
		Parcel* parcel;

	protected:
		virtual ~ParcelDecorator(){
			delete parcel;
		} 

	public:
		ParcelDecorator(Parcel* parcel) : parcel(parcel){}

		virtual string description(){
			return parcel->description();
		}

		bool isPriority() override {
			return parcel->isPriority();
		}

		bool isSigned() override {
			return parcel->isSigned();
		}

		bool isFragile() override {
			return parcel->isFragile();
		}

		bool isLarge() override {
			return parcel->isLarge();
		}

		string getCountry() override {
			return parcel->getCountry();
		}

		string getProvince() override {
			return parcel->getProvince();
		}

		string getCity() override {
			return parcel->getCity();
		}

		string getZipCode() override{
			return parcel->getZipCode();
		}
	
};

class SignedParcel : public ParcelDecorator {
	public:
		SignedParcel(Parcel* parcel) : ParcelDecorator(parcel) {}

		string description() override{
			return ParcelDecorator::description() + " This parcel has to be signed for on delivery.";
		}

		bool isSigned() override{
			return true; 
		}
};

class FragileParcel : public ParcelDecorator {
	public:
		FragileParcel(Parcel* parcel) : ParcelDecorator(parcel) {}

		string description() override{
			return ParcelDecorator::description() + " This parcel is fragile. Handle with care.";
		}
		
		bool isFragile() override{ 
			return true; 
		}
};

class PriorityParcel : public ParcelDecorator {
	public:
		PriorityParcel(Parcel* parcel) : ParcelDecorator(parcel) {}

		string description() override{
			return ParcelDecorator::description() + " This parcel has priority, and should be dispatched as soon as possible.";
		}

		bool isPriority() override{
			return true;
		}
};

class LargeParcel : public ParcelDecorator {
	public:
		LargeParcel(Parcel* parcel) : ParcelDecorator(parcel) {}

		string description() override{
			return ParcelDecorator::description() + " This parcel is large and will require additional space.";
		}

		bool isLarge() override{
			return true;
		}
};



#endif
