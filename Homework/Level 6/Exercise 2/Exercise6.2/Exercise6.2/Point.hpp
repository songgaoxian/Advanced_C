//Point.hpp
//
//declare class Point
//written on 2016/7/14

#ifndef Point_HPP
#define Point_HPP

#include<iostream>
#include"Shape.hpp"

class Point : public Shape
{
private:
	double x, y;
public:
	//default constructor
	Point();
	//constructor with coordinates
	Point(double xs, double ys);
	//copy constructor
	Point(const Point& pt);
	//assignment operator
	Point& operator=(const Point& pt);
	//getter of x
	double X() const;
	//getter of y
	double Y() const;
	//setter of x
	void X(double xs);
	//setter of y
	void Y(double ys);
	//overload ostream operator
	friend std::ostream& operator<<(std::ostream& os, const Point& pt);

	//ab)get distance between two points
	double Distance(const Point& src) const;
	//c)get distance to origin
	double Distance() const;
};



#endif

