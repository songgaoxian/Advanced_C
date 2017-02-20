//Exercise4.10.3
//
//exercise to apply ublas to sparse and triangular matrices
//written on 2016/6/24
#include<boost\numeric\ublas\matrix_sparse.hpp>
#include<boost\numeric\ublas\io.hpp>
#include<boost\numeric\ublas\triangular.hpp>
#include<iostream>
#include<complex>

using c_double = std::complex<double>;
template<typename T>
using sparse_matrix = boost::numeric::ublas::mapped_matrix<T>;

int main() {
	//a)create sparse matrix
	std::size_t row = 3, col = 5, nonzero = 2;
	sparse_matrix<c_double> s_matrix(row, col, nonzero);

	try {
		//experiment with insertion
		std::cout << "a)\ninsert at (0,0):";
		s_matrix.insert_element(0, 0, c_double(1.0, 2.3));
		std::cout<<"successfully\n";

		std::cout << "insert at (1,1):";
		s_matrix.insert_element(1, 1, c_double(2, 3));
		std::cout<<"successfully\n";

		std::cout << "insert at (0,0):";
		s_matrix.insert_element(0, 0, c_double(1, 1));
		std::cout<<"successfully\n";
	}
	catch (...) {
		std::cout << "failure\n";
	}
	//erase element
	try {
		std::cout << "erase at (0,0):";
		s_matrix.erase_element(0, 0);
		std::cout << "successfully\n";
		
		std::cout << "erase at (1,2):";
		s_matrix.erase_element(1, 2);
		std::cout << "successfully\n";
	}
	catch (...) {
		std::cout << "failure\n";
	}
	//clear
	try {
		std::cout << "first time clear:";
		s_matrix.clear();
		std::cout << "successfully\n";

		std::cout << "second time clear:";
		s_matrix.clear();
		std::cout << "successfully\n";
	}
	catch (...) { std::cout << "failure\n"; }

	//b)
	//upper, row-major
	using upper_row_matrix = boost::numeric::ublas::triangular_matrix<double,
		boost::numeric::ublas::upper, boost::numeric::ublas::row_major>;
	//upper, col-major
	using upper_col_matrix = boost::numeric::ublas::triangular_matrix<c_double,
		boost::numeric::ublas::upper, boost::numeric::ublas::column_major>;
	//lower, row-major
	using lower_row_matrix = boost::numeric::ublas::triangular_matrix<double,
		boost::numeric::ublas::lower, boost::numeric::ublas::row_major>;
	//lower, col-major
	using lower_col_matrix = boost::numeric::ublas::triangular_matrix<c_double,
		boost::numeric::ublas::lower, boost::numeric::ublas::column_major>;

	//create matrices
	col = row;
	upper_row_matrix up_rm(row, col); 
	upper_col_matrix up_cm(row, col);
	lower_row_matrix low_rm(row, col);
	lower_col_matrix low_cm(row, col);
	
	for (int i = 0; i < row; ++i) {
		for (int j = i; j < col; ++j) {
			up_rm(i, j) = i*2.1 + j + 0.2;
		}
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j <= i; ++j) {
			low_cm(i, j) = c_double(i*1.1 + 0.1, j*1.1 + 0.2);
		}
	}

	std::cout << "\nb)\nup_rm:" << up_rm << "\nlow_cm:"<<low_cm<<'\n';

	//c)
	boost::numeric::ublas::matrix<double> m(row, col); //upper
	boost::numeric::ublas::matrix<c_double> m1(row, col);//lower
	for (int i = 0; i < row; ++i) {
		for (int j = i; j < col; ++j) {
			m(i, j) = i*1.9 + j*1.1+0.1;
		}
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j <= i; ++j) {
			m1(i, j) = c_double(i*1.9+0.1, j*1.1+0.1);
		}
	}
    //create upper matrix
	boost::numeric::ublas::triangular_adaptor<boost::numeric::ublas::matrix<double>,
		boost::numeric::ublas::upper> t_upper_m(m);
	std::cout << "\nc)\nt_upper_m=" << t_upper_m << '\n';
	//create lower matrix
	boost::numeric::ublas::triangular_adaptor<boost::numeric::ublas::matrix<c_double>,
		boost::numeric::ublas::lower> t_lower_m(m1);
	std::cout << "t_lower=" << t_lower_m << '\n';
	

	return 0;
}