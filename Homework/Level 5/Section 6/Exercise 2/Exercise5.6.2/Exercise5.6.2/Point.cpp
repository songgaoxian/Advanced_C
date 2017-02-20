//Point.cpp
//
//implement Point class
//written on 2016/6/30
#include"Point.hpp"
#include"DistanceStrategy.hpp"


Point& Point::operator=(const Point& pt) { x = pt.x; y = pt.y; return*this; }
double Point::Distance(const Point& src, DistanceStrategy* strategy) const { return strategy->Distance(*this, src); }