//Exercise5.12.1
//
//test classes defined in Propogator.h
//written on 2016/7/2

#include"Propogator.hpp"

int main() {
	Counter c;
	//create observers
	Observer* ob1 = new Counter;
	Observer* ob2 = new Counter;
	Observer* ob3 = new Counter;
	//add to c
	c.AddObserver(ob1);
	c.AddObserver(ob2);
	c.AddObserver(ob3);
	//notify
	std::cout << "Notify current data:\n";
	c.NotifyObservers();

	//increase
	double amount = 1.2;
	std::cout << "\nIncrease counter of c:\n";
	c.Increase(amount);

	//decrease
	amount = 1.1;
	std::cout << "\nDecrease counter of c:\n";
	c.Decrease(amount);

	return 0;
}