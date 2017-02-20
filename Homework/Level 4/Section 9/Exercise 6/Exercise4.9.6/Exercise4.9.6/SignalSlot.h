//SignalSlot.h
//
//implement slots and signals to represent layers
//written on 2016/6/23

#ifndef SignalSlot_H
#define SignalSlot_H
#include<boost\signals2.hpp>
#include<iostream>

//define Exterior
boost::signals2::signal<void(double& d)> exteriorSig;
//define Hardware
boost::signals2::signal<void(double& d)> hardwareSig;
//define Data
boost::signals2::signal<void(double& d)> dataSig;
//define Communication
boost::signals2::signal<void(double& d)> communicationSig;

//create slot for Exterior
void eSlot(double& d) { 
	d *= 2.1;
	std::cout << "in Exterior,d=" << d << '\n';
}

//create slot for Hardware
void hSlot(double& d) {
	if (d >= 2 && d <= 4) {
		d *= 0.9;
	}
	else {
		d = 3.0;
	}
	std::cout << "in Hardware,d=" << d << '\n';
}

//create slot for Data
void dSlot(double& d) {
	d -= 0.2;
	std::cout << "in Data,d=" << d << '\n';
}

//create slot for Communication
void cSlot(double& d) {
	d /= 0.5;
	std::cout << "in Communication, d=" << d << '\n';
}




#endif
