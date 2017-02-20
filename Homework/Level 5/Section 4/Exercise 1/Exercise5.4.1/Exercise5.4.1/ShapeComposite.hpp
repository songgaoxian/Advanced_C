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
	
public:
	ShapeComposite();
	//d)create addshape 
	void AddShape(Shape* s);
	//e)create iterators
	typedef std::list<Shape*>::iterator iter;
	typedef std::list<Shape*>::const_iterator const_iter;

	//f)create begin and end
	const_iter begin() const;
	const_iter end() const;
	//g)return size of composite
	std::size_t count() const;

	virtual bool isShapeComposite();

	//c)add clone()
	virtual Shape* Clone();

	//d)copy constructor
	ShapeComposite(const ShapeComposite& sc);
	//d)assignment operator
	ShapeComposite& operator=(const ShapeComposite& sc);
};

//for completeness
class PolyLine :public ShapeComposite
{
public:
	bool isShapeComposite() { return true; }
	virtual Shape* Clone() { return new PolyLine(*this); }
};




#endif

