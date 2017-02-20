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
	Shape() { std::cout << "a shape created by default\n"; }
	//copy constructor
	Shape(const Shape& shp) { std::cout << "a shape created by copy\n"; }
	//assignment operator
	Shape& operator=(const Shape& shp) {
		std::cout << "assign a shape\n";
		return *this;
	}
};
#endif
