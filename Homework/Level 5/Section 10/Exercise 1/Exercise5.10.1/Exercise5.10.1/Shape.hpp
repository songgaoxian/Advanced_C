//Shape.h
//
//implement classes of Shape, Line, Point, Circle
//written on 2016/6/28
#ifndef Shape_H
#define Shape_H

#include<iostream>
#include<sstream>
#include<string>

class ShapeVisitor;

//base class
class Shape {
public:
	//default constructor
	Shape() { }
	//copy constructor
	Shape(const Shape& shp) {  }
	//assignment operator
	Shape& operator=(const Shape& shp) {
		return *this;
	}
	virtual bool isShapeComposite() = 0;
	//b)a pure virtual function to return a Shape*
	virtual Shape* Clone() = 0;
	//c)add Accept()
	virtual void Accept(ShapeVisitor& sv) = 0;
};

//point
class Point :public Shape
{
private:
	double x, y;
public:
	//default constructor
	Point() :x(0), y(0) {  }
	//constructor with coordinates
	Point(double xs, double ys) :x(xs), y(ys) { }
	//copy constructor
	Point(const Point& pt) :x(pt.x), y(pt.y) {  }
	//assignment operator
	Point& operator=(const Point& pt) {
		x = pt.x;
		y = pt.y;
		return *this;
	}
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

	//ab)get distance between two points
	double Distance(const Point& src) const {
		return sqrt((x - src.x)*(x - src.x) + (y - src.y)*(y - src.y));
	}
	//get distance to origin
	double Distance() const {
		return Distance(Point(0, 0));
	}
	virtual bool isShapeComposite() { return false; }

	//c) add Clone to all shape classes
	virtual Shape* Clone() { return this; }

	//d)implement Accept() method
	virtual void Accept(ShapeVisitor& sv);

};

//line class
class Line :public Shape
{
private:
	Point start_pt, end_pt;
public:
	//default constructor
	Line() :start_pt(Point()), end_pt(Point()) {  }
	//constructor with points
	Line(const Point& pt1s, const Point& pt2s) :start_pt(pt1s), end_pt(pt2s) { }
	//copy constructor
	Line(const Line& line) :start_pt(line.start_pt), end_pt(line.end_pt) {  }
	//assignment operator
	Line& operator=(const Line& line) {
		start_pt = line.start_pt;
		end_pt = line.end_pt;
		return *this;
	}
	//getter of start point
	Point& p1() { return start_pt; }
	//getter of end point
	Point& p2() { return end_pt; }
	//setter of start point
	void p1(const Point& ps) { start_pt = ps; }
	//setter of end point
	void p2(const Point& ps) { end_pt = ps; }

	friend std::ostream& operator<<(std::ostream& os, const Line& line) {
		os << "Line starts at " << line.start_pt << ", ends at " << line.end_pt;
		return os;
	}

	//de)calculate length of the line
	double Length() const {
		return start_pt.Distance(end_pt);
	}
	virtual bool isShapeComposite() { return false; }
	//c)add clone
	virtual Shape* Clone() { return this; }

	//d)implement Accept() method
	virtual void Accept(ShapeVisitor& sv);
};

//circle class
class Circle :public Shape
{
private:
	Point m_centre;
	double m_r;
public:
	//default constructor
	Circle() :m_centre(Point()), m_r(0) { }
	//constructor with point and radius
	Circle(const Point& c, double r) :m_centre(c), m_r(r) {  }
	//copy constructor
	Circle(const Circle& c) :m_centre(c.m_centre), m_r(c.m_r) { }
	//assignment operator
	Circle& operator=(const Circle& c) {
		m_centre = c.m_centre;
		m_r = c.m_r;
		return *this;
	}
	//getter of centre
	Point& CenterPoint() { return m_centre; }
	//getter of radius
	double Radius() const { return m_r; }
	//setter of centre
	void CenterPoint(Point centre) { m_centre = centre; }
	//setter of radius
	void Radius(double radius) { m_r = radius; }

	friend std::ostream& operator<<(std::ostream& os, const Circle& c) {
		os << "Circle centred at " << c.m_centre << " with radius " << c.m_r;
		return os;
	}
	virtual bool isShapeComposite() { return false; }

	//c)add clone
	virtual Shape* Clone() { return this; }

	//d)implement Accept() method
	virtual void Accept(ShapeVisitor& sv);
};

#include"ShapeVisitor.hpp"

#endif
