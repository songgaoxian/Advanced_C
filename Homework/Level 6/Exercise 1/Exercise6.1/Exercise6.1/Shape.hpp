//Shape.hpp
//
//declare base class Shape
//written on 2016/7/14
#ifndef Shape_HPP
#define Shape_HPP

class Shape {
public:
	Shape() {} //default constructor
	Shape(const Shape& shp) {} //copy constructor
	Shape& operator=(const Shape& shp);//assignment operator
	virtual ~Shape() {}
};

#endif

