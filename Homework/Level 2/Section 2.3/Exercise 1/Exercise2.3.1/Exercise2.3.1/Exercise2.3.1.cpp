#include<iostream>
#include<stdio.h>
#include<utility>

//a) create deprecated free function
[[deprecated("old function")]] void print() { std::cout << "hello\n"; }

//b) deprecated class
class bclass {
public:
	void display() const { std::cout << "B class\n"; }
};
[[deprecated("old class")]]
typedef bclass B;
//b) non-deprecated class with deprecated member functions
class A {
public:
	[[deprecated("old member functions")]]
	void display() const { std::cout << "A class\n"; }
};

//c) deprecated global variable
[[deprecated("old variable")]]
double olddouble = 2.2;

//d) deprecated enum
enum days { yesterday, today, tomorrow };
[[deprecated("old enum")]]
typedef days Days;
//d) deprecated enum class
enum class timed { yesterday, today, tomorrow };
[[deprecated("old enum class")]]
typedef timed Timed;

//e)deprecated template class specialization
template<typename T>
class ABC {};

template<>
class ABC<int> {};
[[deprecated("old template specialization")]]
typedef ABC<int> abcInt;

//f)deprecated lambda function
[[deprecated("old lambda")]]
auto f1 = [](double x) {return x; };

int main() {
	//print(); //show error message: 'print': old function
	//B b; //show error message: 'B': old class
	A a; //no error
		 //a.display(); //show error message: 'A::display': old member functions
		 //double ndouble = olddouble; //show error message: 'olddouble': old variable
		 //Days d = today; //show error message: 'Days': old enum
		 //Timed t = timed::today; //show error message: 'Timed': old enum class
	ABC<double> abcD; //no error
					  //abcInt abcI; //show error message: 'abcInt': old template specialization
	double x = 1.1; //to be used in f1
					//f1(x); //show error message: 'f1': old lambda
	return 0;
}