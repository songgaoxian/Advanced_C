//ShapeVisitor.cpp
//
//implement ShapeVisitor, PrintVisitor and TranslateVisitor classes
//written on 2016/7/2

#include"Shape.hpp"
#include"ShapeComposite.hpp"
#include"ShapeVisitor.hpp"

void ShapeVisitor::Visit(ShapeComposite& s) {
	for (auto it = s.begin(); it != s.end(); it++) {
		(*it)->Accept(*this);
	}
}
//e)implement Visit for class PrintVisitor
void PrintVisitor::Visit(Point& p) { std::cout << p; }
void PrintVisitor::Visit(Line& l) { 
	std::cout << "Line:"; 
	Visit(l.p1()); Visit(l.p2());
}
void PrintVisitor::Visit(Circle& c) {
	std::cout << "Circle with radius "<<c.Radius()<<" centred at ";
	Visit(c.CenterPoint());

}
void PrintVisitor::Visit(ShapeComposite& s) {
	this->ShapeVisitor::Visit(s);
}

//initialize static d
double TranslateVisitor::d = 0;
//implement Visit for class TranslateVisitor
void TranslateVisitor::Visit(Point& p) {
	p.X(p.X() + d);
	p.Y(p.Y() + d);
}
void TranslateVisitor::Visit(Line& l) {
	l.p1().X(l.p1().X() + d);
	l.p1().Y(l.p1().Y() + d);

	l.p2().X(l.p2().X() + d);
	l.p2().Y(l.p2().Y() + d);
}
void TranslateVisitor::Visit(Circle& c) {
	c.CenterPoint().X(c.CenterPoint().X() + d);
	c.CenterPoint().Y(c.CenterPoint().Y() + d);
}
void TranslateVisitor::Visit(ShapeComposite& s) {
	this->ShapeVisitor::Visit(s);
}