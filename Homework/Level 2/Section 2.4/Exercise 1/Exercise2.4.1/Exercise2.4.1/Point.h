#ifndef Point_H
#define Point_H
#include<iostream>
class Point {
private:
	double x;
	double y;
public:
	Point(double srcx, double srcy) :x(srcx), y(srcy) { std::cout << "point is created\n"; }
	void X(const double srcx) { x = srcx; }
	void Y(const double srcy) { y = srcy; }
	virtual ~Point() { std::cout << "bye point\n"; }
};
#endif
