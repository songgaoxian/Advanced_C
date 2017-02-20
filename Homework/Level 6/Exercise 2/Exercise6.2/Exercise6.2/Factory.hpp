//Factory.hpp
//
//declare Single class and related classes
//written on 2016/7/14

#ifndef Factory_HPP
#define Factory_HPP

#include"Shape.hpp"
#include"Point.hpp"
#include"Line.hpp"
#include"Circle.hpp"
#include<functional>
#include<tuple>

class ConsoleShapeFactory
{
public:
	//d)implement create shape functions
	virtual Shape* CreateCircle();

	virtual Shape* CreatePoint();

	virtual Shape* CreateLine();
};

using funcShape = std::function<Shape*()>;

//composition of factory methods
class Single {
private:
	funcShape CreatePoint;
	funcShape CreateLine;
	funcShape CreateCircle;
public:
	//constructor
	Single(funcShape pt, funcShape line, funcShape circle);
	std::tuple<Shape*, Shape*, Shape*> run();
};


#endif

