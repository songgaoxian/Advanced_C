//Point.h
//
//create class Point
//written on 2016/6/30
#ifndef Point_H
#define Point_H

#include<iostream>
#include<sstream>
#include<string>
#include"DistanceStrategy.hpp"
//point
class Point
{
private:
	double x, y;
	static DistanceStrategy* strategy; //d)add a static member
public:
	//default constructor
	Point() :x(0), y(0) {  }
	//constructor with coordinates
	Point(double xs, double ys) :x(xs), y(ys) { }
	//copy constructor
	Point(const Point& pt) :x(pt.x), y(pt.y) {  }
	//assignment operator
	Point& operator=(const Point& pt);
	//getter of x
	double X() const { return x; }
	//getter of y
	double Y() const { return y; }
	//setter of x
	void X(double xs) { x = xs; }
	//setter of y
	void Y(double ys) { y = ys; }
	//overload ostream operator
	friend std::ostream& operator<<(std::ostream& os, const Point& pt) {
		os << "Point(" << pt.x << "," << pt.y << ")";
		return os;
	}

	//d)add static method to set strategy
	static void SetStrategy(DistanceStrategy* src) { strategy = src; };


	//e)modify Distance() to use strategy
	//ab)get distance between two points
	double Distance(const Point& src) const;
	//get distance to origin
	double Distance() const;
};

#endif
