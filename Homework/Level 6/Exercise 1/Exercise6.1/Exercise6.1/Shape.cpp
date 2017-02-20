//Shape.cpp
//
//implement Shape class
//written on 2016/7/14

#include<iostream>
#include"Shape.hpp"

Shape& Shape::operator=(const Shape& shp) {
	std::cout << "assign a shape\n";
	return *this;
}