//Shape.cpp
//
//implement Shape and derived classes
//written on 2016/7/12

#include"Shape.hpp"

Shape& Shape::operator=(const Shape& shp) {
	std::cout << "assign a shape\n";
	return *this;
}

//implement Point
Point::Point() :Shape(), x(0), y(0) {  }
Point::Point(double xs, double ys) : Shape(), x(xs), y(ys) { }
Point::Point(const Point& pt) : Shape(pt), x(pt.x), y(pt.y) {  }
Point& Point::operator=(const Point& pt) {
	Shape::operator=(pt);
	x = pt.x;
	y = pt.y;
	return *this;
}
double Point::X() const { return x; }
double Point::Y() const { return y; }
void Point::X(double xs) { x = xs; }
void Point::Y(double ys) { y = ys; }
//friend function
std::ostream& operator<<(std::ostream& os, const Point& pt) {
	os << "Point(" << pt.x << "," << pt.y << ")";
	return os;
}
double Point::Distance(const Point& src) const {
	return std::sqrt((x - src.x)*(x - src.x) + (y - src.y)*(y - src.y));
}
double Point::Distance() const {
	return Distance(Point(0, 0));
}
//end

//implement Line
Line::Line() :Shape(), start_pt(Point()), end_pt(Point()) {  }
Line::Line(const Point& pt1s, const Point& pt2s) : Shape(), start_pt(pt1s), end_pt(pt2s) { }
Line::Line(const Line& line) : Shape(line), start_pt(line.start_pt), end_pt(line.end_pt) {  }
Line& Line::operator=(const Line& line) {
	Shape::operator=(line);
	start_pt = line.start_pt;
	end_pt = line.end_pt;
	return *this;
}
Point Line::p1() const { return start_pt; }
Point Line::p2() const { return end_pt; }
void Line::p1(const Point& ps) { start_pt = ps; }
void Line::p2(const Point& ps) { end_pt = ps; }
//friend function
std::ostream& operator<<(std::ostream& os, const Line& line) {
	os << "Line starts at " << line.start_pt << ", ends at " << line.end_pt;
	return os;
}
double Line::Length() const {
	return start_pt.Distance(end_pt);
}
//end

//implement Circle
Circle::Circle() :Shape(), m_centre(Point()), m_r(0) { }
Circle::Circle(const Point& c, double r) : Shape(), m_centre(c), m_r(r) {  }
Circle::Circle(const Circle& c) : Shape(c), m_centre(c.m_centre), m_r(c.m_r) { }
Circle& Circle::operator=(const Circle& c) {
	Shape::operator=(c);
	m_centre = c.m_centre;
	m_r = c.m_r;
	return *this;
}
Point Circle::CenterPoint() const { return m_centre; }
double Circle::Radius() const { return m_r; }
void Circle::CenterPoint(Point centre) { m_centre = centre; }
void Circle::Radius(double radius) { m_r = radius; }
//friend function
std::ostream& operator<<(std::ostream& os, const Circle& c) {
	os << "Circle centred at " << c.m_centre << " with radius " << c.m_r;
	return os;
}
//end