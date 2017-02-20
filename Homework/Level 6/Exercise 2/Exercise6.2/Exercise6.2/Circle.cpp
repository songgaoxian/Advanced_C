//Circle.cpp
//
//implement class Circle
//written on 2016/7/14

#include"Circle.hpp"
#include<iostream>

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