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

	virtual bool isShapeComposite() { return true; }

	//c)add clone()
	virtual Shape* Clone() { return this; }

	//d)copy constructor
	ShapeComposite(const ShapeComposite& sc) {
		for (auto it = sc.begin(); it != sc.end(); it++) {
			//push cloned copy to lst
			lst.push_back((*it)->Clone());
		}
	}
	//d)assignment operator
	ShapeComposite& operator=(const ShapeComposite& sc) {
		lst.clear();
		//push cloned copy to lst
		for (auto it = sc.begin(); it != sc.end(); it++) {
			lst.push_back((*it)->Clone());
		}
		return *this;
	}
	virtual void Accept(ShapeVisitor& sv);
};

//for completeness
class PolyLine :public ShapeComposite
{
public:
	bool isShapeComposite() { return true; }
	virtual Shape* Clone() { return this; }
};




#endif
