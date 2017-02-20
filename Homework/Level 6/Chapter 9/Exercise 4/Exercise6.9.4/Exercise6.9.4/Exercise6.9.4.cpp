//Exercise6.9.4
//test codes

#include"DVM_Interface.hpp"
#include"DVM_Imp.hpp"

int main() {
	//declare required variables
	Source src;
	Auth au;
	Resource rs;
	Sink sk;
	MIS mis;
	//declare and construct object dvm
	DVM dvm(src, au, rs, sk, mis);
	//start the DVM operation
	dvm.run();

	return 0;
}
//PBD implementation is more efficient as there are less classes required to be created for PBD;
//PBD is more maintainable. When we need to change some method of certain interface, we need to change base class
//and derived class for current method while we only need to change one class or recreate a new class corresponding to
//the interface;
//PBD is more extendible. Just create new classes with extended functionality and add these new classes as template parameters to DVM if using PBD;
//For current method, we need to create new hierarchies of classes and change codes in class DVM, resulting in more coding work and breaking info hinding;
//PBD is more replaceable by just using different class as template parameter for DVM. But for current method, we need to change codes in class DVM
//Overall, PBD is better for this case.

//using function wrappers can result in more flexible and maintainable codes; using boost signals2 can simultaneously call several functions which
//improves efficiency and reducing coding work. But using function wrappers and signals2 may provide access to changing functionality without enough authorization
//as it is easier for client to create malfunctioning function which is assigned to a wrapper or used as a slot for signal
