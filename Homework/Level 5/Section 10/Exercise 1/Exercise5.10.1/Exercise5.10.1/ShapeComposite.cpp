//ShapeComposite.cpp
//
//implement ShapeComposite and PolyLine classes
//written on 2016/7/2

#include"Shape.hpp"
#include"ShapeComposite.hpp"
#include"ShapeVisitor.hpp"
//d)implement Accept()
void ShapeComposite::Accept(ShapeVisitor& sv) { sv.Visit(*this); }