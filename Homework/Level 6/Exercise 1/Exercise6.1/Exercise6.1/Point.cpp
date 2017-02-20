//Point.cpp
//
//implement Point class
//written on 2016/7/14

#include"Point.hpp"

Point::Point() :Shape(), x(0), y(0) {  }
Point::Point(double xs, double ys) : Shape(), x(xs), y(ys) { }
Point::Point(const Point& pt) : Shape(pt), x(pt.x), y(pt.y) {  }
Point& Point::operator=(const Point& pt) {
	Shape::operator=(pt);
	x = pt.x;
	y = pt.y;
	return *this;
}
double Point::X() const { return x; }
double Point::Y() const { return y; }
void Point::X(double xs) { x = xs; }
void Point::Y(double ys) { y = ys; }
//friend function
std::ostream& operator<<(std::ostream& os, const Point& pt) {
	os << "Point(" << pt.x << "," << pt.y << ")";
	return os;
}
double Point::Distance(const Point& src) const {
	return std::sqrt((x - src.x)*(x - src.x) + (y - src.y)*(y - src.y));
}
double Point::Distance() const {
	return Distance(Point(0, 0));
}