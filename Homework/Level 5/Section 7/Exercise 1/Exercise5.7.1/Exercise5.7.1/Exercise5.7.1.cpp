//Exercise5.7.1
//
//Test ShapeFactory to create some shapes
//written on 2016/6/30

#include"Shape.hpp"
#include"ShapeFactory.hpp"

int main() {
	ShapeFactory* sfy = new ConsoleShapeFactory;
	//create circle
	Circle c = *dynamic_cast<Circle*>(sfy->CreateCircle());
	//create point
	Point pt =*dynamic_cast<Point*>(sfy->CreatePoint());
	//create line
	Line line =*dynamic_cast<Line*>(sfy->CreateLine());
	//print out c, pt and line
	std::cout << "\nCircle created:\n" << c << '\n';
	std::cout << "\nPoint created:\n" << pt << '\n';
	std::cout << "\nLine created:\n" << line << '\n';

	return 0;
}