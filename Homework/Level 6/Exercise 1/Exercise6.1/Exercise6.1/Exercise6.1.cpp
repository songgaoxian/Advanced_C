//Exercise6.1
//
//test new codes
//written on 2016/7/14

#include"Shape.hpp"
#include"Circle.hpp"
#include"Point.hpp"
#include"Line.hpp"
#include"Factory.hpp"
#include<iostream>

int main() {
	ShapeFactory* shpf = new ConsoleFactory;
	//create shapes
	std::tuple<Shape*, Shape*, Shape*> shapes = shpf->CreateShapes();
	//get shapes
	Shape* shape1 = std::get<0>(shapes);
	Shape* shape2 = std::get<1>(shapes);
	Shape* shape3 = std::get<2>(shapes);
	//print out
	std::cout << "\nThe following shapes are created:\n";
	std::cout << *dynamic_cast<Point*>(shape1) << '\n';
	std::cout << *dynamic_cast<Line*>(shape2) << '\n';
	std::cout << *dynamic_cast<Circle*>(shape3) << '\n';

	return 0;

}
//If we use GOF solution and need to add a new shape, eg rectangle,we will need to add new function CreateRectangle
//to base class and all derived classes;
//If we use the new solution and need to add rectangle, we don't need to add any functions but need to add additional codes
//to create rectangle to ConsoleFactory class, the workload of which is somewhat less than the worload of GOF solution