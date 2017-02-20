//Exercise5.3.1
//
//test shape composite and print out shape composite
//written on 2016/6/29


#include"Singleton.hpp"
#include"Shape.hpp"
#include"Point.hpp"
#include"ShapeComposite.hpp"
#include"OriginPoint.hpp"
#include<iostream>
//h
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
			std::cout << *(dynamic_cast<Point*>(obj)) << " ";
		}
		start++;
	}
}

int main() {
	//construct shape composites
	ShapeComposite sc;
	sc.AddShape(new Point(1, 1));
	sc.AddShape(new Point(3, 3));
	sc.AddShape(new Point(4, 3));
	ShapeComposite sc2;
	sc2.AddShape(new Point(5, 4));
	sc2.AddShape(&sc);
	sc2.AddShape(new Point(6, 9));
	sc2.AddShape(&sc);
	
	//print recursively
	Print(sc2);
	//print the size
	std::cout << "\nSize of sc2=" << sc2.count() << '\n';
	return 0;
}