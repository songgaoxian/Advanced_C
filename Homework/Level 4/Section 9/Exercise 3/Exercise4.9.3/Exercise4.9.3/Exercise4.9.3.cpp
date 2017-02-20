//Exercise4.9.3
//
//exercise to use combiner
//written on 2016/6/23

#include<boost\signals2.hpp>
#include"CombinerSlot.h"


int main() {
	//a)
	boost::signals2::signal<bool(), BootstrapCheck> sig;
	//c)connect slots to sig
	sig.connect(&slot1);
	sig.connect(&slot2);
	sig.connect(&slot3);
	//call sig
	auto result=sig();
	std::cout << "sig returns " << std::boolalpha << result << '\n';
	return 0;
}