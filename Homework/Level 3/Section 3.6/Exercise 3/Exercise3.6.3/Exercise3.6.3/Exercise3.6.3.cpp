#include "Matrix.h"
#include<iostream>

//print function
template<typename T, int NR, int NC>
void print(Matrix<T, NR, NC>& matrix) {
	for (int i = 0; i < NR; ++i) {
		std::cout << std::endl;
		for (int j = 0; j < NC; ++j)
			std::cout << matrix(i,j) << " ";
	}
	std::cout << std::endl;
}
int main() {
	const int NR = 3;
	const int NC = 4;
	Matrix<double, NR, NC> m; //default
	Matrix<double,NR,NC> m1(13.2); 
	int val2 = 9;
	Matrix<int, NR, NC> m2(val2);//construct with value
	double val3 = 1.3;
	Matrix<double, NR, NC> m3(val3);
	//print out
	std::cout << "print m1:";
	print<double, NR, NC>(m1);
	std::cout << "print m2: ";
	print<int, NR, NC>(m2);
	std::cout << "print m3: ";
	print<double, NR, NC>(m3);
	//check access
	m2(1,1) = 2;
	std::cout << "printf m2 after access\n";
	print<int, NR, NC>(m2);
	//check add, subtract, unary and premultiplicaation
	std::cout << "check add, subtract, unary and premultiplicaation";
	print<double, NR, NC>(m1 + m3);
	print<double, NR, NC>(m3 - m1);
	print<double, NR, NC>(-m3);
	double val = 2;
	print<double, NR, NC>(m3*val);
	//check scalar multiply
	print<double, NR, NC>(2 * m3);
	//check modify
	m3.modify([](double x) {return x / 2; });
	print<double, NR, NC>(m3);

	return 0;
}