//Shape.h
//
//implement classes of Shape, Line, Point, Circle
//written on 2016/6/28
#ifndef Shape_H
#define Shape_H

#include<iostream>

//base class
class Shape {
public:
	//default constructor
	Shape();
	//copy constructor
	Shape(const Shape& shp);
	//assignment operator
	Shape& operator=(const Shape& shp);
	virtual bool isShapeComposite() = 0;
	//b)a pure virtual function to return a Shape*
	virtual Shape* Clone() = 0;

};

//point
class Point :public Shape
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
	//get distance to origin
	double Distance() const;
	virtual bool isShapeComposite();

	//c) add Clone to all shape classes
	virtual Shape* Clone();
};

//line class
class Line :public Shape
{
private:
	Point start_pt, end_pt;
public:
	//default constructor
	Line();
	//constructor with points
	Line(const Point& pt1s, const Point& pt2s);
	//copy constructor
	Line(const Line& line);
	//assignment operator
	Line& operator=(const Line& line);
	//getter of start point
	Point p1() const;
	//getter of end point
	Point p2() const;
	//setter of start point
	void p1(const Point& ps);
	//setter of end point
	void p2(const Point& ps);

	friend std::ostream& operator<<(std::ostream& os, const Line& line);

	//de)calculate length of the line
	double Length() const;
	virtual bool isShapeComposite();
	//c)add clone
	virtual Shape* Clone();
};

//circle class
class Circle :public Shape
{
private:
	Point m_centre;
	double m_r;
public:
	//default constructor
	Circle();
	//constructor with point and radius
	Circle(const Point& c, double r);
	//copy constructor
	Circle(const Circle& c);
	//assignment operator
	Circle& operator=(const Circle& c);
	//getter of centre
	Point CenterPoint() const;
	//getter of radius
	double Radius() const;
	//setter of centre
	void CenterPoint(Point centre);
	//setter of radius
	void Radius(double radius);

	friend std::ostream& operator<<(std::ostream& os, const Circle& c);
	virtual bool isShapeComposite();

	//c)add clone
	virtual Shape* Clone();
};



#endif