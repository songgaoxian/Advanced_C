//Point.cpp
//
//Specify methods of Point class
//written on 2016/6/29
#include"Point.hpp"
#include"OriginPoint.hpp"

Point::Point() :x(0), y(0) {}
Point::Point(double xs, double ys) : x(xs), y(ys) {}
Point::Point(const Point& pt) : x(pt.x), y(pt.y) {}
Point& Point::operator=(const Point& src) {
	x = src.x;
	y = src.y;
	return *this;
}
double Point::X() const { return x; }
double Point::Y() const { return y; }
void Point::X(double xs) { x = xs; }
void Point::Y(double ys) { y = ys; }
double Point::Distance(const Point& src) const {
	double x_dif = x - src.x;
	double y_dif = y - src.y;
	return sqrt(x_dif*x_dif + y_dif*y_dif);
}
//c)change Distance() function
double Point::Distance() const {
	return Distance(*OriginPoint::instance());
}
bool Point::isShapeComposite() { return false; }