//Shape.h
//
//declare and implement class Shape
//written on 2016/6/29
#ifndef Shape_H
#define Shape_H
#include<iostream>

//base class
class Shape {
public:
	//default constructor
	Shape() { }
	//copy constructor
	Shape(const Shape& shp) { }
	//assignment operator
	Shape& operator=(const Shape& shp) {
		return *this;
	}
	//check if it is a shape composite
	virtual bool isShapeComposite() { return false; }
};
#endif