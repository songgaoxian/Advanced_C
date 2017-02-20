//ShapeDecorator.h
//
//create ShapeDecorator and NameDecorator classes
//written on 2016/7/1

#ifndef Decorator_H
#define Decorator_H

#include"Shape.hpp"
#include"ShapeComposite.hpp"

//a)create ShapeDecorator
class ShapeDecorator: public Shape 
{
private:
	//b)shape to decorate
	Shape* shp;
public:
	//c)default constructor
	ShapeDecorator() :Shape() {
		shp = nullptr;
	}
	//d)constructor with Shape*
	ShapeDecorator(Shape* src) { shp = src; }
	//e)GetShape to return decorated shape
	Shape* GetShape()const{ return shp; }
	//SetShape to set decorated shape
	void SetShape(Shape* src) { shp = src; }
	virtual Shape* Clone() = 0;
	virtual bool isShapeComposite() { return false; }
};

//f)create new class NameDecorator
class NameDecorator :public ShapeDecorator
{
private:
	//g)name data member
	std::string name;
public:
	//h)default constructor
	NameDecorator() :ShapeDecorator(),name("") {}
	//i)constructor with Shape* and string
	NameDecorator(Shape* src, std::string s) :ShapeDecorator(src), name(s) {}
    //j)GetName function to return name
	std::string GetName() const { return name; }
	//SetName to set name
	void SetName(std::string s) { name = s; }
	//k)implement Clone
	virtual Shape* Clone() { return this; }
	virtual bool isShapeComposite() { return false; }
};




#endif
