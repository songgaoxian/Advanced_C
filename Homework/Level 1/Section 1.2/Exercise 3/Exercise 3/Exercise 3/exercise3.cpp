#include"C.h"
#include<iostream>
int main() {
	//use a std::move to call the constructor
	std::vector<double> v{ 1.1,2.2,3.3 };
	C source(v);
	C movecreatedC(std::move(source));
	std::cout << "print movecreatedC:\n";
	movecreatedC.print();
	C moveassignedC;
	std::cout << "moveassignedC before assignment:\n";
	moveassignedC.print();
	std::cout << "moveassignedC after assignment:\n";
	moveassignedC = C(v);
	moveassignedC.print();
	//source is a lvalue
	C target;
//	target.moveOps(source); //it will incur error when using lvalue for moveOps
	target.moveOps(std::move(source)); //this version is ok
	return 0;
}