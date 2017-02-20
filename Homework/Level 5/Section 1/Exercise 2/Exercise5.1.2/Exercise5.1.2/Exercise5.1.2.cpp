//Exercise5.1.2
//
//delegate length of line to distance of points and test
//written on 2016/6/28

#include"Shape.hpp"

int main() {
	//f)test Distance and Length
	//create objects of points
	Point origin(0, 0);
	Point pt1(1, 2);
	Point pt2(3, 4);
	//create line
	Line line(pt1, pt2);
	//get distance btw pt1 and pt2
	std::cout << "distance btw pt1 and pt2: " << pt1.Distance(pt2) << '\n';
	//get length of line
	std::cout << "line has length of " << line.Length() << '\n';
	//get distance btw pt1 and origin
	std::cout << "distance btw pt1 and origin: " << pt1.Distance(origin) << '\n';
	//get distance btw pt1 and origin use another Distance function
	std::cout << "distance btw pt1 and origin(another Distance): " << pt1.Distance() << '\n';

	return 0;

}