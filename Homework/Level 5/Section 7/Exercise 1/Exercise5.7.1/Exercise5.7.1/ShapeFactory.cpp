//ShapeFactory.cpp
//
//implement ShapeFactory and derived classes
//written on 2016/7/12

#include"ShapeFactory.hpp"

Shape* ConsoleShapeFactory::CreateCircle() {
	double c_x, c_y, c_r;
	//prompt for input from user
	std::cout << "Give x coordinate of the circle centre:\n";
	std::cin >> c_x;
	std::cout << "Give y coordinate of the circle centre:\n";
	std::cin >> c_y;
	std::cout << "Give radius of the circle:\n";
	std::cin >> c_r;
	//return created Circle
	return new Circle(Point(c_x, c_y), c_r);
}
Shape* ConsoleShapeFactory::CreatePoint() {
	double x, y;
	//prompt for user input
	std::cout << "Give x coordinate of the point:\n";
	std::cin >> x;
	std::cout << "Give y coordinate of the point:\n";
	std::cin >> y;
	//return point
	return new Point(x, y);
}
Shape* ConsoleShapeFactory::CreateLine() {
	double start_x, start_y, end_x, end_y;
	//prompt for user input
	std::cout << "Give x coordinate of the start point of line:\n";
	std::cin >> start_x;
	std::cout << "Give y coordinate of the start point of line:\n";
	std::cin >> start_y;

	std::cout << "Give x coordinate of end point of line:\n";
	std::cin >> end_x;
	std::cout << "Give y coordinate of end point of line:\n";
	std::cin >> end_y;

	//return line
	return new Line(Point(start_x, start_y), Point(end_x, end_y));
}