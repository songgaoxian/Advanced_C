#ifndef Base_H
#define Base_H
#include<iostream>
struct Base {
	virtual void draw() { std::cout << "print a base\n"; }
	virtual void print(){}
	~Base() { std::cout << "bye base\n"; }
};
struct Derived : public Base {
	Derived() {}
	void draw() override { std::cout << "print a derived\n"; }
	void draw() const {}
	void print() override {}
	~Derived() { std::cout << "bye derived\n"; }
};
class Derived2 final: public Derived{};
#endif