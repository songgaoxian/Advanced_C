//Point2.cpp
//
//implement Point2 class
//written on 2016/6/30
#include"Point2.hpp"

int Point2::counter = 0;
//statebased version
Point2::Point2(const dist_algo& alg) :x(0), y(0),algo(alg) {  }
Point2::Point2(double xs, double ys, const dist_algo& alg) : x(xs), y(ys),algo(alg) { }
Point2::Point2(const Point2& pt) : x(pt.x), y(pt.y),algo(pt.algo) {  }

double Point2::X() const { return x; }
double Point2::Y() const { return y; }

void Point2::X(double xs) { x = xs; }
void Point2::Y(double ys) { y = ys; }

Point2& Point2::operator=(const Point2& pt) { x = pt.x; y = pt.y; algo = pt.algo; return*this; }
//friend function
std::ostream& operator<<(std::ostream& os, const Point2& pt) {
	os << "Point2(" << pt.x << "," << pt.y << ")";
	return os;
}

double Point2::Distance(const Point2& pt) { return algo(x, y, pt.x, pt.y,Point2::counter); }
