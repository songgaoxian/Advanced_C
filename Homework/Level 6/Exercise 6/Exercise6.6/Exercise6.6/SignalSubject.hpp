//SignalSubject.hpp
//
//declare Signal version Subject and Counter classes
#ifndef Signal_HPP
#define Signal_HPP

#include<list>
#include<iostream>
#include<functional>
#include<string>
#include<boost\signals2.hpp>
#include"Subject.hpp"

//a)create SignalSubject class
class SignalSubject {
private:
	boost::signals2::signal<void()> lst;
	Func LongFormat;
	Func DoubleFormat;
	int sigNum;
public:
	SignalSubject();
	virtual void Attach(std::string choice);
	virtual void Detach();
	virtual void Notify();
};
//b)create SignalCounter class
class SignalCounter :public SignalSubject
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
	SignalCounter() :value(0) {}
};
#endif