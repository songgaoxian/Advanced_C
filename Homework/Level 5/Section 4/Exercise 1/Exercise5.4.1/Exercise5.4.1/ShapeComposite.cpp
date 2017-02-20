//ShapeComposite.cpp
//
//implement ShapeComposite class and derived class
//written on 2016/7/12

#include"ShapeComposite.hpp"

//implement ShapeComposite
ShapeComposite::ShapeComposite() :Shape() { }

void ShapeComposite::AddShape(Shape* s) { lst.push_back(s); }

ShapeComposite::const_iter ShapeComposite::begin() const {return lst.begin();}

ShapeComposite::const_iter ShapeComposite::end() const {return lst.end();}

std::size_t ShapeComposite::count() const { return lst.size(); }

bool ShapeComposite::isShapeComposite() { return true; }

Shape* ShapeComposite::Clone() { return new ShapeComposite(*this); }

ShapeComposite::ShapeComposite(const ShapeComposite& sc):Shape(sc) {
	for (auto it = sc.begin(); it != sc.end(); it++) {
		//push cloned copy to lst
		lst.push_back((*it)->Clone());
	}
}
ShapeComposite& ShapeComposite::operator=(const ShapeComposite& sc) {
	Shape::operator=(sc);
	lst.clear();
	//push cloned copy to lst
	for (auto it = sc.begin(); it != sc.end(); it++) {
		lst.push_back((*it)->Clone());
	}
	return *this;
}

