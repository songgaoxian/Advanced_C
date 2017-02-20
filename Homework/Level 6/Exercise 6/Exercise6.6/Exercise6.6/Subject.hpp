//Subject.h
//
//create Subject and Counter classes
//written on 2016/7/2

#ifndef Subject_H
#define Subject_H

#include<list>
#include<iostream>
#include<functional>
#include<string>

using Func = std::function<void()>;

//a)create Subject class
//use template template implementation
template<typename F,typename A,template<typename,typename>class Container>
class Subject {
private:
	Container<F,A> lst;
	F LongFormat;
	F DoubleFormat;
public:
	Subject();
	virtual void Attach(std::string choice);
	virtual void Detach();
	virtual void Notify();
};
//b)create Counter class
//template template implementation
template<typename F,typename A,template<typename,typename>class Container>
class Counter :public Subject<F,A,Container>
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
	Counter() :value(0) {}
};

#include"Subject.cpp"
#endif

