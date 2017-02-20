#ifndef C_H
#define C_H
#include<memory>
#include<iostream>
#include "Point.h"
using std::cout;

//for a and c)
//create class C1 with shared object
class C1 {
private:
	//std::shared_ptr<double> d; //for a)
	std::shared_ptr<Point> p; //for c)
public:
	//C1(std::shared_ptr<double> value):d(value){} //for a)
	C1(std::shared_ptr<Point> value):p(value){} //for c)
	virtual ~C1() { cout << "\nC1 destructor\n"; }
	void print() const { cout << "Value " << *p; }
};
//create class C2 with shared object
class C2 {
private:
	//std::shared_ptr<double> d; //for a)
	std::shared_ptr<Point> p; //for c)
public:
	//C2(std::shared_ptr<double> value) :d(value) {} //for a)
	C2(std::shared_ptr<Point> value): p(value) {} //for c)
	virtual ~C2() { cout << "\nC2 destructor\n"; }
	void print() const { cout << "Value " << *p; }
};
//end of a)
#endif