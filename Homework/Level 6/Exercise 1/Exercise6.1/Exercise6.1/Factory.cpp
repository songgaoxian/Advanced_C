//Factory.cpp
//
//implement factory classes
//written on 2016/7/14

#include"Factory.hpp"

std::tuple<Shape*, Shape*, Shape*> ConsoleFactory::CreateShapes() {
	//declare variables for shapes's parameters
	double pt_x, pt_y, start_x, start_y,end_x,end_y, c_x, c_y, r;

	//create point
	std::cout << "Let's create a point!\n";
	std::cout << "X?";
	std::cin >> pt_x;
	std::cout << "Y?";
	std::cin >> pt_y;
	//end

	//create line
	std::cout << "\nLet's create a line!\n";
	std::cout << "X of start point?";
	std::cin >> start_x;
	std::cout << "Y of start point?";
	std::cin >> start_y;
	Point start = Point(start_x, start_y);

	std::cout << "X of end point?";
	std::cin >> end_x;
	std::cout << "Y of end point?";
	std::cin >> end_y;
	Point end = Point(end_x, end_y);
	//end

	//create circle
	std::cout << "\nLet's create a circle!\n";
	std::cout << "X of centre?";
	std::cin >> c_x;
	std::cout << "Y of centre?";
	std::cin >> c_y;
	std::cout << "Radius?";
	std::cin >> r;
	Point c = Point(c_x, c_y);
	//end

	return std::make_tuple<Shape*, Shape*, Shape*>(new Point(pt_x, pt_y), new Line(start, end), new Circle(c, r));
}

std::tuple<Shape*, Shape*, Shape*> WindowsFactory::CreateShapes() {
	return std::make_tuple<Shape*, Shape*, Shape*>(new Point(), new Line(), new Circle());
}