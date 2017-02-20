#include "VectorMatrix.h"
#include<iostream>


//print out function
template<typename T,int N>
void print(Vector<T, N>& v) {
	for (int i = 0; i < N; ++i)
		std::cout << v[i] << " ";
}

int main() {
	//b)create instances of Vector
	const int N = 10;
	//default
	Vector<double, N> v;
	//with value
	Vector<double, N> v1(0);
	//with value
	int val = 4;
	Vector<int, N> v2(val);
	//print out
	print<double, N>(v1);
	std::cout << std::endl;
	print<int, N>(v2);
	std::cout << std::endl;
	//check access
	v2[0] = 5;
	std::cout << "access to v2[0]=" << v2[0] << std::endl;
	//check scalar multiply
	Vector<double, N> v3 = N*v1;
	print<double, N>(v3);
	std::cout<<std::endl;
	
	Vector<int, N> v4(10);
	//check add
	print<int, N>(v4+v2);
	std::cout << std::endl;
	//check subtract
	print<int, N>(v2 - v4);
	std::cout << std::endl;
	//check unary minus
	print<int, N>(-v2);
	std::cout << std::endl;
	//check premultiplication
	print<int, N>(v2 * 5);
	std::cout << std::endl;
	//check modify
	const std::function<int(int&)> f1 = [](int& x) {return x * 2; };
	v2.modify(f1);
	print<int, N>(v2);
	return 0;

}