//Point2.hpp
//
//create class Point
//written on 2016/6/30
#ifndef Point2_H
#define Point2_H

#include<iostream>
#include<functional>
#include"Point.hpp" //just use dist_algo

//stateful version
//point
class Point2
{
private:
	double x, y;
	dist_algo algo;
	static int counter;
public:
	static int Getcounter() { return counter; }
    //constructor
	Point2(const dist_algo& alg);
	//constructor with coordinates
	Point2(double xs, double ys,const dist_algo& alg);
	//copy constructor
	Point2(const Point2& pt);
	//assignment operator
	Point2& operator=(const Point2& pt);
	//getter of x
	double X() const;
	//getter of y
	double Y() const;
	//setter of x
	void X(double xs);
	//setter of y
	void Y(double ys);
	//overload ostream operator
	friend std::ostream& operator<<(std::ostream& os, const Point2& pt);
	//calculate distance
	double Distance(const Point2& pt);
};

#endif


