//ShapeVisitor.h
//
//create ShapeVisitor, PrintVisitor and TranslateVisitor classes
//written on 2016/7/2

#ifndef ShapeVisitor_H
#define ShapeVisitor_H

#include"Shape.hpp"
#include"ShapeComposite.hpp"

//a)create base class
class ShapeVisitor {
public:
	//create Visit method
	virtual void Visit(Point& p) = 0;
	virtual void Visit(Line& l) = 0;
	virtual void Visit(Circle& c) = 0;
	//b)implement Visit for ShapeComposite
	virtual void Visit(ShapeComposite& s);
};
//e)new class
class PrintVisitor :public ShapeVisitor
{
public:
	//all the Visit method
	virtual void Visit(Point& p);
	virtual void Visit(Line& l);
	virtual void Visit(Circle& c);
	virtual void Visit(ShapeComposite& s);
};
//translate class
class TranslateVisitor :public ShapeVisitor
{
private:
	static double d; //the distance to translate
public:
	//all the Visit method
	virtual void Visit(Point& p);
	virtual void Visit(Line& l);
	virtual void Visit(Circle& c);
	virtual void Visit(ShapeComposite& s);
	//set the distance to translate
	static void Set(double x) { d = x; }
};







#endif
