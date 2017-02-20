//Subject.h
//
//create Subject and Counter classes
//written on 2016/7/2

#ifndef Subject_H
#define Subject_H

#include<list>
#include<iostream>

class Observer;
//a)create Subject class
class Subject {
private:
	std::list<Observer*> lst;
public:
	virtual void Attach(Observer* obs);
	virtual void Detach();
	virtual void Notify();
};
//b)create Counter class
class Counter :public Subject
{
private:
	double value; //c)private variable holds counter value
public:
	//e)return counter value
	virtual double GetCounter() { return value; }
	//f)Increate counter value and notify
	virtual void IncreaseCounter(double increment);
	//g)Decreate counter
	virtual void DecreaseCounter(double decrement);
	//h)default constructor
	Counter():value(0){}
};


#include"Observer.hpp"

#endif
