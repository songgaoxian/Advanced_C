//Point.h
//
//implement Point class
//written on 2016/6/20

#ifndef Point_H
#define Point_H
#include<string>
#include<sstream>

class Point {
private:
	double x, y;
public:
	//constructors
	Point():x(0),y(0){}
	Point(double srcx, double srcy) :x(srcx), y(srcy) {}
	//getters
	double X() const { return x; }
	double Y() const { return y; }
	//setters
	void X(double src) { x = src; }
	void Y(double src) { y = src; }
	//give a string
	std::string Point_s() const {
		std::stringstream ss;
		ss << "(" << x << "," << y << ")";
		return ss.str();
	}
	//overload equal operator
	friend bool operator==(const Point& pt1, const Point& pt2) {
		return (pt1.x == pt2.x) && (pt1.y == pt2.y);
	}
	//overload unequal operator
	friend bool operator!=(const Point& pt1, const Point& pt2) {
		return !(pt1 == pt2);
	}
	//overload <
	friend bool operator<(const Point&pt1, const Point&pt2) {
		if (pt1.x < pt2.x) return true;
		if (pt1.x == pt2.x && pt1.y < pt2.y) return true;
		return false;
	}
};

#endif
