//Exercise4.9.6
//
//implement layered communication with signals
//written on 2016/6/23

#include"SignalSlot.h"

int main() {
	//b)connect signals and slots
	//start with exterior
	exteriorSig.connect(0, &eSlot);
	double value = -3.7;
	//emit exterior
	std::cout << "emit exterior:\n";
	exteriorSig(value);

	//hardware
	hardwareSig.connect(0, &hSlot);
	//emit hardware
	std::cout << "\nemit hardware:\n";
	hardwareSig(value);

	//data
	dataSig.connect(0, &dSlot);
	//emit data
	std::cout << "\nemit data:\n";
	dataSig(value);

	//communication
	communicationSig.connect(0, &cSlot);
	//emit data
	std::cout << "\nemit communication:\n";
	communicationSig(value);

	//connect signals
	exteriorSig.connect(1, hardwareSig);
	hardwareSig.connect(1, dataSig);
	dataSig.connect(1, communicationSig);

	value = -3.7;
	std::cout << "\nAfter combining all slots and signals:\n";
	exteriorSig(value);

	return 0;
	
}