//Line.cpp
//
//implement class Line
//written on 2016/7/14

#include"Line.hpp"
#include<iostream>

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