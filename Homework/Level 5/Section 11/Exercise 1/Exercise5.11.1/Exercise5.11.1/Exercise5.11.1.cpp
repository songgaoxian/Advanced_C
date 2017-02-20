//Exercise5.11.1
//
//test Subject and derived classes, Observer and derived classes
//written on 2016/7/2

#include"Observer.hpp"
#include"Subject.hpp"

int main(){
	//create counter object
	Counter c;
	//create observers
	LongFormat lf1, lf2;
	DoubleFormat df1, df2;
	
	//attach to c
	c.Attach(&lf1);
	c.Attach(&df1);
	c.Attach(&lf2);
	c.Attach(&df2);
	
	//notify
	c.Notify();
	std::cout << "End of Notification\n";
	
	//increment
	double increment = 4.9;
	std::cout << "\nIncrease counter c by " << increment << ":\n";
	c.IncreaseCounter(increment);
	std::cout << "End of Increment Operation\n";
	//detach
	c.Detach();
	c.Detach();
	
	//decrement
	double decrement = 0.6;
	std::cout << "\nDecrease counter c by " << decrement << ":\n";
	c.DecreaseCounter(decrement);
	std::cout << "End of Decrement Operation\n";

	return 0;
}