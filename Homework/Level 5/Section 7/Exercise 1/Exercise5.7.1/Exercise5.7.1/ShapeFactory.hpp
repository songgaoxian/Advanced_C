//ShapeFactory.h
//
//create ShapeFactory and ConsoleShapeFactory classes
//written on 2016/6/30

#ifndef ShapeFactory_H
#define ShapeFactory_H

#include"Shape.hpp"

//base class
//a)
class ShapeFactory {
public:
	//b)create pure virtual functions
	virtual Shape* CreateCircle() = 0;
	virtual Shape* CreatePoint() = 0;
	virtual Shape* CreateLine() = 0;
};
//c)create derived class
class ConsoleShapeFactory :public ShapeFactory
{
public:
	//d)implement create shape functions
	virtual Shape* CreateCircle();

	virtual Shape* CreatePoint();

	virtual Shape* CreateLine();
};



#endif
