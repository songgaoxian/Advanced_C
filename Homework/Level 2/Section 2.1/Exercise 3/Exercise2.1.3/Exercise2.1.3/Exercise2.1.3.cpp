#include "Class.h"
#include<type_traits>
#include<iostream>
using std::cout;

//part a's question is answered by running this function
template<typename T>
void Check(const T& t) {
	//check if type T is empty
	cout << "is empty? " << std::boolalpha << std::is_empty<T>::value << std::endl;
	//check if type T is polymorphic
	cout << "is polymorphic? " << std::boolalpha << std::is_polymorphic<T>::value << std::endl;
	//check if type T is abstract
	cout << "is abstract? " << std::boolalpha << std::is_abstract<T>::value << std::endl;
}

//part b-c's questions are answered by running this function
template<typename T1, typename T2>
void CheckRelation(const T1& t1, const T2& t2) {
	//check if T1 and T2 are same
	cout << "is same? " << std::boolalpha << std::is_same<T1, T2>::value << std::endl;
	//check if T1 and T2 are convertible
	cout << "is convertible? " << std::boolalpha << std::is_convertible<T1, T2>::value << std::endl;
	//check if there exists base/derived relation
	cout << "does there exist base/derived relation? ";
	if (std::is_base_of<T1, T2>::value || std::is_base_of<T2, T1>::value) {
		//if T1 is the base of T2 or T2 is the base of T1, print true
		cout << "true\n";
	}
	else {
		//otherwise, print false
		cout << "false\n";
	}
}

int main() {
	//declare and initialize variables to test functionality and answer a)-d)
	Base b;
	Point pt1, pt2;
	Shape& sp = pt2;
	//answer question a) for Base b
	cout << "Base b: ";
	Check(b);
	//answer question a) for Point pt1
	cout << "Point pt1: ";
	Check(pt1);
	//answer question a) for Shape& sp
	cout << "Shape& sp: ";
	Check(sp);
	//answer question b-d) for Point pt1 and pt2
	cout << "Point pt1 and Point pt2: ";
	CheckRelation(pt1, pt2);
	//answer question b-d) for Base b and Shape& sp
	cout << "Base b and Shape& sp: ";
	CheckRelation(b, sp);
	//answer question b-d) for Shape& sp and Point pt1
	cout << "Shape& sp and Point pt1: ";
	CheckRelation(sp, pt1);
	return 0;
}