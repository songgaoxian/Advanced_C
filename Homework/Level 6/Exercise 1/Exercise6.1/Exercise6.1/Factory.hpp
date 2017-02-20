//Factory.hpp
//
//declare factory classes
//written on 2016/7/14

#ifndef Factory_HPP
#define Factory_HPP

#include"Shape.hpp"
#include"Point.hpp"
#include"Line.hpp"
#include"Circle.hpp"
#include<tuple>

//base class
class ShapeFactory {
public:
	virtual std::tuple<Shape*, Shape*, Shape*> CreateShapes() = 0;
};
//derived class
class ConsoleFactory : public ShapeFactory
{
public:
	virtual std::tuple<Shape*, Shape*, Shape*> CreateShapes();
};
//for completeness
class WindowsFactory :public ShapeFactory
{
public:
	virtual std::tuple<Shape*, Shape*, Shape*> CreateShapes();
};
#endif