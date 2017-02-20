//ShapeComposite.h
//
//declare and implement class ShapeComposite, derived from Shape
//written on 2016/6/29
#ifndef ShapeComposite_H
#define ShapeComposite_H
#include<list>
#include"Shape.hpp"

//a)create ShapeComposite class 
//assume only points or shape composite can be put into shape composite



class ShapeComposite :public Shape
{
private:
	//b)declare list data member
	std::list<Shape*> lst;
	//c)create private copy constructor and assignment operator
	ShapeComposite(const ShapeComposite& src); //copy constructor
	ShapeComposite& operator=(const ShapeComposite& src);//assignment operator

public:
	ShapeComposite() :Shape() { }
	//d)create addshape 
	void AddShape(Shape* s) { lst.push_back(s); }
	//e)create iterators
	typedef std::list<Shape*>::iterator iter;
	typedef std::list<Shape*>::const_iterator const_iter;
	//f)create begin and end
	const_iter begin() const {
		return lst.begin();
	}
	const_iter end() const {
		return lst.end();
	}
	
	//g)return size of composite
	std::size_t count() const { return lst.size(); }
	
	//check if it is a ShapeComposite
	bool isShapeComposite() { return true; }
};

//for completeness
class PolyLine :public ShapeComposite
{
public:
	bool isShapeComposite() { return true; }
};





#endif
