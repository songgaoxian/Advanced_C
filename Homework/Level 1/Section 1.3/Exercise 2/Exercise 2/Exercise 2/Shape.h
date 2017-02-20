#ifndef Shape_H
#define Shape_H
#include <iostream>
class Shape {
public:
	virtual void rotate(double d) = 0;
};

class Circle : public Shape {
public:
	void rotate(double d) override { std::cout << "c\n"; }
};

class Line : public Shape {
public:
	void rotate(double d) override { std::cout << "l\n"; }
};

class Valve {
public:
	void rotate(double d) { std::cout << "v\n"; }
};
#endif
