//Exercise5.10.1
//
//test visitors
//written on 2016/7/2
#include"Shape.hpp"
#include"ShapeComposite.hpp"
#include"ShapeVisitor.hpp"

int main() {
	//create a polyline
	PolyLine pline;
	pline.AddShape(new Point(1, 2));
	pline.AddShape(new Point(2, 2));
	pline.AddShape(new Point(3, 3));
	//create PrintVisitor
	PrintVisitor pv;
	//print polyline
	pv.Visit(pline);
    
	//test translate visitor
	TranslateVisitor::Set(1);
	TranslateVisitor tv;
	tv.Visit(pline);
	//print polyline
	std::cout << "\nafter translation:\n";
	pv.Visit(pline);

	//create ShapeComposite
	ShapeComposite sc;
	sc.AddShape(new Point(3, 5));
	Point p1(4, 2);
	Point p2(3, 9);
	sc.AddShape(new Line(p1, p2));
	sc.AddShape(new Circle(Point(4, 5), 5.5));
	std::cout << "\nPrint sc:\n";
	pv.Visit(sc);
	std::cout << "\nAfter translation:\n";
	tv.Visit(sc);
	pv.Visit(sc);
	std::cout << "\n\n";

	ShapeComposite sc2;
	sc2.AddShape(new Point(0, 0));
	sc2.AddShape(&sc);
	sc2.AddShape(new Circle(Point(0, 1), 1.2));
	sc2.AddShape(&sc);
	sc2.AddShape(new Point(0, 0));
	std::cout << "\nPrint sc2:\n";
	//print out
	pv.Visit(sc2);

	return 0;
}