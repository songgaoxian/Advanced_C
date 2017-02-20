//Exercise4.10.2
//
//implement dense matrices with ublas
//written on 2016/6/24
#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\io.hpp>
#include<iostream>
#include<complex>

using c_double = std::complex<double>;
namespace ublas = boost::numeric::ublas;

int main() {
	//a)specify dimension
	std::size_t row = 4, col = 2;
	//create matrices
	ublas::matrix<double,ublas::column_major,ublas::unbounded_array<double>> ublas_m1(row, col,0.0);
	ublas::matrix<c_double,ublas::row_major,ublas::bounded_array<c_double,8>> ublas_m2(row, col,0.0);

    //b)use() to access modify elements
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			ublas_m1(j, i) = double(i + j) / 1.1;
			ublas_m2(j, i) = c_double(i*2.1+1,j*1.1+1);
		}
	}
	//print out
	std::cout << "ublas_m1:" << ublas_m1 << '\n';
	std::cout << "ublas_m2:" << ublas_m2 << '\n';

	//c)
	//create two more matrices
	ublas::matrix<double, ublas::column_major, ublas::unbounded_array<double>> ublas_m3(row, col, 1.5);
	ublas::matrix<c_double, ublas::row_major, ublas::bounded_array<c_double, 8>> ublas_m4(row, col, c_double(1.1, 2.1));
	//print out
	std::cout << "\nublas_m3:" << ublas_m3 << '\n';
	std::cout << "ublas_m4:" << ublas_m4 << '\n';

	//add ublas_m2 and ublas_m4
	auto ublas_add = ublas_m2 + ublas_m4;
	//subtract ublas_m1 and ublas_m3
	auto ublas_sub = ublas_m1 - ublas_m3;
	std::cout << "add ublas_m2 and ublas_m4:" << ublas_add << '\n';
	std::cout << "subtract ublas_m1 and ublas_m3:" << ublas_sub << '\n';

	//d)resize ublas_m1
	ublas_m1.resize(3, 5);
	std::cout << "\nafter resize:size1=" << ublas_m1.size1() << "; size2=" << ublas_m1.size2() << '\n';

	//e)
	//create zero matrix
	ublas::zero_matrix<double> uz(2, 3);
	ublas::zero_matrix<c_double> uz2(2, 3);
	//create identity matrix
	ublas::identity_matrix<c_double> ui(3);
	ublas::identity_matrix<double> ui2(3);
	//print out
	std::cout << "\nzero_matrix<double>:" << uz << '\n';
	std::cout << "zero_matrix<complex>:" << uz2 << '\n';
	std::cout << "identity_matrix<complex>:" << ui << '\n';
	std::cout << "identity_matrix<double>:" << ui2 << '\n';


	return 0;

}