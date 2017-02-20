//Exercise5.4.1
//
//test shape composite and print out shape composite
//written on 2016/6/29

#include"Shape.hpp"
#include"ShapeComposite.hpp"
#include<iostream>

void Print(ShapeComposite& sc) {
	ShapeComposite::const_iter start = sc.begin();
	ShapeComposite::const_iter end = sc.end();
	while (start != end) {
		auto obj = *start;
		if (obj->isShapeComposite()) {
			//if obj is ShapeComposite, recursively call Print
			Print(*dynamic_cast<ShapeComposite*>(obj));
		}
		else {
			//assume only Points or ShapeComposites are embedded in sc
			//std::cout << *(dynamic_cast<Point*>(obj)) << " ";//point version
			//std::cout << *(dynamic_cast<Line*>(obj)) << " ";//line version
			std::cout << *(dynamic_cast<Circle*>(obj)) << " ";//circle version
		}
		start++;
	}
}

int main() {
	//construct shape composites
	ShapeComposite sc;
	//sc.AddShape(new Point(1, 1));//point version
	//sc.AddShape(new Point(3, 3));//point version
	//sc.AddShape(new Point(4, 3));//point version
	//sc.AddShape(new Line(Point(1, 1), Point(1, 2)));//line version
	//sc.AddShape(new Line(Point(1, 3), Point(5, 6)));//line version
	//sc.AddShape(new Line(Point(3, 5), Point(9, 9)));//line version
	sc.AddShape(new Circle(Point(1, 2), 2));//circle version
	sc.AddShape(new Circle(Point(2, 3), 1));//circle version

	ShapeComposite sc2;
	//sc2.AddShape(new Point(5, 4));//point version
	//sc2.AddShape(new Line(Point(1, 6), Point(4, 6)));//line version
	sc2.AddShape(&sc);
	//sc2.AddShape(new Point(6, 9));//point version
	//sc2.AddShape(new Line(Point(6, 6), Point(9, 9)));//line version
	sc2.AddShape(new Circle(Point(5, 5), 5));//circle version
	sc2.AddShape(&sc);

	//print recursively
	std::cout << "Print sc2:\n";
	Print(sc2);
	std::cout << '\n';
	//apply copy constructor
	ShapeComposite sc3(sc2);
	std::cout << "Print copy of sc2:\n";
	Print(sc3);
	std::cout << '\n';
	//apply assignment operator
	ShapeComposite sc4;
	sc4 = sc2;
	std::cout << "Print sc4 which is assigned by sc2:\n";
	Print(sc4);
	std::cout << '\n';


	return 0;
}