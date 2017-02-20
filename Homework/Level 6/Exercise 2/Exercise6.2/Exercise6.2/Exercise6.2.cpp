//Exercise6.2
//
//test new codes
//written on 2016/7/14

#include"Shape.hpp"
#include"Point.hpp"
#include"Circle.hpp"
#include"Line.hpp"
#include"Factory.hpp"
#include<iostream>

//lambda function
auto createPoint = []() ->Shape*
{
	//declare variables
	double x, y;

	std::cout << "\nCreate point!\n";
	std::cout << "X?";
	std::cin >> x;
	std::cout << "Y?";
	std::cin >> y;

	return new Point(x, y);
};

//function object
struct createLine {
	//constructor
	createLine() {}
	//operator()
	Shape* operator()() {
		std::cout << "\ncreate Line:\n";
		//get start point
		Point start = *dynamic_cast<Point*>(createPoint());
		//get end point
		Point end = *dynamic_cast<Point*>(createPoint());
		return new Line(start, end);
	}
};

int main() {
	//instantiate factory methods in Single class
	ConsoleShapeFactory csf;
	funcShape createCircle = std::bind(&ConsoleShapeFactory::CreateCircle, &csf);
	Single s(createPoint, createLine(), createCircle);
	//run s
	std::tuple<Shape*, Shape*, Shape*> shapes = s.run();
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
//Compared to GOF design, this new design adds more flexibility. 
//The usage of std::function is like delegates in C#. We do not need to modify codes in classes if the only change is just the delegate.
//Overall, it is more reusable and suitable for other patterns

//Just like the code given in Exercise 6.2, we can integrate existing OOP code by using delegates (std::function, for example)
//as members and applying lambda functions or using std::bind to instantiate these members.

//modify objects using captured variables:
//assume factory is the pointer to the object to be modified and the target value
//is variable val: then use the lambda function as follows:
//auto lambda_modify=[&val,&factory](){
// //modify factory by calling modify methods with target value val
//  factory->modify_method(val);
// }