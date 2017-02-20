#ifndef Class_H
#define Class_H
#include<iostream>
using std::cout;

class Base {
	//Base class
private:
	
public:
	Base(){}
	virtual void print() const = 0;
protected:
	virtual ~Base() { cout << "Base destructor\n\n"; }
};

class Derived : public Base
{
private:

public:
	Derived():Base(){}
	~Derived() { cout << "Derived destructor\n"; }
	void print() const { cout << "derived object\n"; }
};
#endif
