//ShapeFactory.cpp
//
//implement ShapeFactory and derived classes
//written on 2016/7/12

#include"ShapeFactory.hpp"

Shape* ShapeFactory::CreateLine(const PointCreator& p_create) {
	std::cout << "\nLet's create a line!\n";
	//create start and end points
	Point start_pt = *dynamic_cast<Point*>(p_create());
	Point end_pt = *dynamic_cast<Point*>(p_create());
	return new Line(start_pt, end_pt);
}

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
	std::cout << "\nCreate point\n";
	double x, y;
	//prompt for user input
	std::cout << "Give x coordinate of the point:\n";
	std::cin >> x;
	std::cout << "Give y coordinate of the point:\n";
	std::cin >> y;
	//return point
	return new Point(x, y);
}
