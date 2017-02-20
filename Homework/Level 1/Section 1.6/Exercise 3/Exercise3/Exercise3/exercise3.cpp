#include<iostream>
using namespace std;
struct B {
	explicit B(int){} //To make "B b1=1" compile, remove the keyword "explicit" in this line
	explicit B(int,int){}
	explicit operator int() const { return 0; }
};

int main() {
	//B b1 = 1; //not compile due to explicit constructor
	B b2(3);
	B b3{ 7,3 };
	B b4 = (B)42;
	// the above three statements compile
	
	return 0;
}