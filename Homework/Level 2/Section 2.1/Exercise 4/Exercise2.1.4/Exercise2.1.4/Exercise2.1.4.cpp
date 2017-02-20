#include "Shape.h"
#include <iostream>
#include<type_traits>
using std::cout;

template<typename T>
void Check(const T& t) {
	//a) programmatically determine if there is a virtual destructor
	cout << "has a virtual destructor? " << std::boolalpha << std::has_virtual_destructor<T>::value << std::endl;
	//b) programmatically determine if there is a default constructor
	cout << "has default constructor? " << std::boolalpha << std::is_default_constructible<T>::value << std::endl;
	//b) programmatically determine if there is a copy constructor
	cout << "has copy constructor? " << std::boolalpha << std::is_copy_constructible<T>::value << std::endl;
	//b) programmatically determine if there is a move constructor
	cout << "has move constructor? " << std::boolalpha << std::is_move_constructible<T>::value << std::endl;
	//c) programmatically determine if it is move assignable
	cout << "is it move assignable? " << std::boolalpha << std::is_move_assignable<T>::value << std::endl;
	//c) programmatically determine if it is copy assignable
	cout << "is it copy assignable? " << std::boolalpha << std::is_copy_assignable<T>::value << std::endl;
}

int main() {
	//create Point for checking a)-c)
	Point pt;
	//create Point1 for part d)
	Point1 pt1;
	//create Point2 for part e)
	Point2 pt2;
	cout << "Check Point: \n";
	//display result for part a)-c)
	Check(pt);
	cout << "Check Point1 for part d):\n";
	//display result for part d)
	Check(pt1);
	//display result for part e)
	cout << "Check Point2 for part e):\n";
	Check(pt2);
	//results are different and are displayed as above
	return 0;
}