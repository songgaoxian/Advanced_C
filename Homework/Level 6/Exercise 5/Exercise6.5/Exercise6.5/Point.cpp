//Point.cpp
//
//implement Point class
//written on 2016/6/30
#include"Point.hpp"

int Point::counter = 0;
//stateless version
Point::Point() :x(0), y(0) {  }
Point::Point(double xs, double ys) :x(xs), y(ys) { }
Point::Point(const Point& pt) :x(pt.x), y(pt.y) {  }

double Point::X() const { return x; }
double Point::Y() const { return y; }

void Point::X(double xs) { x = xs; }
void Point::Y(double ys) { y = ys; }

Point& Point::operator=(const Point& pt) { x = pt.x; y = pt.y; return*this; }
//friend function
std::ostream& operator<<(std::ostream& os, const Point& pt) {
	os << "Point(" << pt.x << "," << pt.y << ")";
	return os;
}
//increment counter in algo
double Point::Distance(const Point& pt, const dist_algo& algo) { 
	return algo(x, y, pt.x, pt.y,Point::counter);
}
