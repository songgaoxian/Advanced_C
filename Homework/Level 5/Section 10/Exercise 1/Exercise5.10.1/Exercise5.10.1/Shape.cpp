//Shape.cpp
//
//implement Shape, Point, Line and Circle classes
//written on 2016/7/2

#include"Shape.hpp"
#include"ShapeComposite.hpp"
#include"ShapeVisitor.hpp"

//d)implement Accept()
void Point::Accept(ShapeVisitor& sv) { sv.Visit(*this); }
void Line::Accept(ShapeVisitor& sv) { sv.Visit(*this); }
void Circle::Accept(ShapeVisitor& sv) { sv.Visit(*this); }