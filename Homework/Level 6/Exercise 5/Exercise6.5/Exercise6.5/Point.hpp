//Point.h
//
//create class Point
//written on 2016/6/30
#ifndef Point_H
#define Point_H

#include<iostream>
#include<functional>

//interface to compute distance
using dist_algo = std::function<double(double x1, double y1, double x2, double y2,int& count)>;

//stateless version
//point
class Point
{
private:
	double x, y;
	static int counter;
public:
	static int Getcounter() { return counter; }
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
	//calculate distance
	double Distance(const Point& pt, const dist_algo& algo);
};

#endif

