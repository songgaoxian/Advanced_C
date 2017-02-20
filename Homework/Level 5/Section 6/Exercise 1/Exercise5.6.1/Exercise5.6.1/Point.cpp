//Point.cpp
//
//implement Point class
//written on 2016/6/30
#include"Point.hpp"
#include"DistanceStrategy.hpp"

DistanceStrategy* Point::strategy = new ExactDistance;//initialise static variable
Point& Point::operator=(const Point& pt) { x = pt.x; y = pt.y; return*this; }
double Point::Distance(const Point& src) const { return strategy->Distance(*this, src);}
double Point::Distance() const { return strategy->Distance(*this, Point(0, 0)); }