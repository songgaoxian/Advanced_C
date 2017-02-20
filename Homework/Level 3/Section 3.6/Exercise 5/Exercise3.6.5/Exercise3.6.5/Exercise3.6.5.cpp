#include"Vector.h"
#include"Matrix.h"
#include<iostream>
#include<numeric>
#include<complex>
//a)
//implement first version inner_product
template<typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initVal) {
	return std::inner_product(v1.It(0),v1.It(N),v2.It(0), initVal);
}
//copied
template<typename T>
using BinaryFunction = std::function<T(const T& t1, const T& t2)>;
//implement second version inner_product
template<typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initval, const BinaryFunction<T>& op1, const BinaryFunction<T>& op2) {
	return std::inner_product(v1.It(0), v1.It(N),v2.It(0), initval, op1, op2);
}

using CBle = std::complex<double>;

//c)Addition
auto ADD = [](auto& val1, auto& val2) {return val1 + val2; };
//multiply
auto MUL = [](auto& val1, auto& val2) {return val1*val2; };

//d)outer product
template<typename T,int NR,int NC>
Matrix<T, NR, NC> outerProduct(Vector<T, NR>& first, Vector<T, NC>& second) {
	//store result of outerproduct
	Matrix<T, NR, NC> result(0);
	//conduct outerproduct
	for (int i = 0; i < NR; ++i)
		for (int j = 0; j < NC; ++j)
			result(i,j) = first[i] * second[j];
	return result;
}

//get conjugate
template<typename T,int N>
Vector<T,N> conjugate(Vector<T, N>& src) {
	for (int i = 0; i < N; ++i)
		src[i] = std::conj(src[i]);
	return src;
}

// print function
template<typename T, int NR, int NC>
void print(Matrix<T, NR, NC>& matrix) {
	for (int i = 0; i < NR; ++i) {
		std::cout << std::endl;
		for (int j = 0; j < NC; ++j)
			std::cout << matrix(i, j) << " ";
	}
	std::cout << std::endl;
}

int main() {
	const int N = 3;
	double val1 = 1.2, val2 = 1,val3=2;
	const int M = 6;
	//create two Vectors with double
	Vector<double, N> vd1(val1);
	Vector<double, N> vd2(val2);
	
	//create two Vectors with CBle
	Vector<CBle, N> vc1(CBle(val1, val2));
	Vector<CBle, N> vc2(CBle(val2, val2));
	//b)Test first variant
	std::cout << inner_product<double, N>(vd1, vd2, 0)<<std::endl;
	std::cout << inner_product<CBle, N>(vc1, vc2, CBle(0, 0)) << std::endl;
		
	//c)test second variant
	//ADD and MUL
	std::cout << inner_product<double, N>(vd1, vd2, 0, ADD, MUL) << std::endl;
	std::cout << inner_product<CBle, N>(vc1, vc2, CBle(0, 0), ADD, MUL) << std::endl;
	//ADD only
	std::cout << inner_product<double, N>(vd1, vd2, 0, ADD, ADD) << std::endl;
	std::cout << inner_product<CBle, N>(vc1, vc2, CBle(0, 0), ADD, ADD) << std::endl;
	//MUL only
	std::cout << inner_product<double, N>(vd1, vd2, 0, MUL, MUL) << std::endl;
	std::cout << inner_product<CBle, N>(vc1, vc2, CBle(0, 0), MUL, MUL) << std::endl;
	//MUL and ADD
	std::cout << inner_product<double, N>(vd1, vd2, 0, MUL, ADD) << std::endl;
	std::cout << inner_product<CBle, N>(vc1, vc2, CBle(0, 0), MUL, ADD) << std::endl;

   //d)test outerproduct
	Vector<double, M> vd3(val3);
	Vector<double, N> vd4(val1);
	std::cout << "print outerproduct result:\n";
	print<double, N, M>(outerProduct(vd4, vd3));
	//e)outerproduct of complex variables
	Vector<CBle, M> vc3(CBle(val2, val3));
	Vector<CBle, N>vc4(CBle(val2, val2));
	std::cout << "print outerproduct of complex variables:\n";
	print<CBle, N, M>(outerProduct(vc4, conjugate(vc3)));


	return 0;
}