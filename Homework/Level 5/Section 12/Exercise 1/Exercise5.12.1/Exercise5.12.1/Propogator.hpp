//Propogator.h
//
//create classes for Propogator pattern
//written on 2016/7/2

#ifndef Propogaotr_H
#define Propogator_H

#include<iostream>
#include<list>

class Observer;
class Counter;
//create Observable class
class Observable {
private:
	std::list<Observer*> lst;
public:
	virtual void AddObserver(Observer* obs);
	virtual void DeleteObserver();
	virtual void NotifyObservers();
};
//create Observer class
class Observer {
public:
	virtual void Update(Observable& obs) = 0;
};
//inherit two classes
class Counter :public Observer, public Observable
{
private:
	double counter;
public:
	double GetCounter() { return counter; }
	void Update(Observable& obs) {
		
		counter = dynamic_cast<Counter&>(obs).GetCounter();
		std::cout << "After update:counter=" << counter << '\n';
	}
	//increase operation
	void Increase(double amount) {
		counter += amount;
		this->NotifyObservers();
	}
	//decrease operation
	void Decrease(double amount) {
		counter -= amount;
		this->NotifyObservers();
	}
	//default constructor
	Counter():counter(0){}
};




#endif
