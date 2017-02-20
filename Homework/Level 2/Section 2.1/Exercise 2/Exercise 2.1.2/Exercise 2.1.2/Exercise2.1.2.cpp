#include<type_traits>
#include<iostream>
using std::cout;
//this function implements IsPointer
//if input type of T is pointer type, it prints the value pointed to
template<typename T>
void implement(const T& t, std::true_type) {
	cout << "it is a pointer pointing to " << *t << std::endl;
}
//this function implements IsPointer
//if the input type of T is not a pointer type, prints the value directly
template<typename T>
void implement(const T& t, std::false_type) {
	cout << "it is not a pointer with value " << t << std::endl;
}
//the function IsPointer calls its implementations
template<typename T>
void IsPointer(const T& t) {
	implement(t, std::is_pointer<T>());
}
int main() {
	//declare and initialize variables to test IsPointer
	int* intp = new int;
	*intp = 15;
	double x = 12.2;
	//call IsPointer function
	IsPointer(intp);
	IsPointer(x);
	delete intp;
	return 0;
}