//Exercise6.6.cpp
//
//test codes and create observer functions

//note:set SDL to -sdl, otherwise, it will give error C4996
#include"Subject.hpp"
#include<deque>
#include"SignalSubject.hpp"


int main() {
	//create counter object
	Counter<Func,std::allocator<Func>,std::deque> c;
	//attach observers
	c.Attach("long");
	c.Attach("double");
	c.Attach("long");
	c.Attach("double");

	//notify
	c.Notify();
	std::cout << "End of Notification\n";

	//increment
	double increment = 4.9;
	std::cout << "\nIncrease counter by " << increment << ":\n";
	c.IncreaseCounter(increment);
	std::cout << "End of Increment\n";
	//detach
	c.Detach();
	c.Detach();

	//decrement
	double decrement = 0.6;
	std::cout << "\nDecrease counter by " << decrement << ":\n";
	c.DecreaseCounter(decrement);
	std::cout << "End of Decrement\n";

	
	//signal2 version
	std::cout << "\n**The Boost Signal2 version**\n";
	//create counter object
	SignalCounter sc;
	//attach observers
	sc.Attach("long");
	sc.Attach("double");
	sc.Attach("long");
	sc.Attach("double");

	//notify
	sc.Notify();
	std::cout << "End of Notification\n";

	//increment
	std::cout << "\nIncrease counter by " << increment << ":\n";
	sc.IncreaseCounter(increment);
	std::cout << "End of Increment\n";
	//detach
	sc.Detach();
	sc.Detach();

	//decrement
	std::cout << "\nDecrease counter by " << decrement << ":\n";
	sc.DecreaseCounter(decrement);
	std::cout << "End of Decrement\n";

	return 0;
}