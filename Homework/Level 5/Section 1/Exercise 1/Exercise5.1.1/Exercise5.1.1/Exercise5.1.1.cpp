//Exercise5.1.1
//
//implement shape hierarchy and test this hierarchy
//written on 2016/6/28
#include"Shape.hpp"

void printAllShape(Shape& shptr) {
	shptr.Print();
	std::cout << '\n';
}

int main() {
	Point pt1(1.1, 2.1);
	Point pt2(3, 4);
	//print pt1 and pt2
	printAllShape(pt1);
	printAllShape(pt2);

	Line line(pt1, pt2);
	//print line
	printAllShape(line);

	Circle c(pt2, 0.8);
	//print c
	printAllShape(c);

	return 0;
}