//Exercise6.3
//
//Test ShapeFactory to create some shapes
//written on 2016/7/14

#include"Shape.hpp"
#include"ShapeFactory.hpp"
#include<vector>
#include<list>
#include<deque>
#include"PolyLine.hpp"
#include"PolyLineFactory.hpp"


int main() {
	ShapeFactory* sfy = new ConsoleShapeFactory;
	//create point
	Point pt = *dynamic_cast<Point*>(sfy->CreatePoint());
	//create line
	Line line = *dynamic_cast<Line*>(sfy->CreateLine(std::bind(&ShapeFactory::CreatePoint,sfy)));
	//print out pt and line
	std::cout << "\nPoint created:\n" << pt << '\n';
	std::cout << "\nLine created:\n" << line << '\n';

   //test polyline class and its factory
	//PolyLine<Point, std::allocator<Point>, std::vector>* poly;//vector version
	//PolyLine<Point, std::allocator<Point>, std::list>* poly;//list version
	PolyLine<Point, std::allocator<Point>, std::deque>* poly;//deque version

	//create the creation function
	Creator<Shape> c = std::bind(&ShapeFactory::CreatePoint, sfy);
	
	//create factory for polyline
	//PolyLineFactory<Point, std::allocator<Point>, Shape, std::vector> poly_factory(c);//vector version
	//PolyLineFactory<Point, std::allocator<Point>, Shape, std::list> poly_factory(c);//list version
	PolyLineFactory<Point, std::allocator<Point>, Shape, std::deque> poly_factory(c);//deque version

	poly = poly_factory.CreatePolyLine();
	//display created line
	poly->Display();




	return 0;
}