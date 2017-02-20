//Exercise4.10.6
//
//use and create matrix and vector proxies
//written on 2016/6/25

#include<boost\numeric\ublas\matrix_proxy.hpp>
#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\io.hpp>
#include<iostream>

int main() {
	int row = 2, col = 4;
	boost::numeric::ublas::matrix<double> m_double(row,col);
	//assign values to m_double
	for (std::size_t i = 0; i < row; ++i) {
		for (std::size_t j = 0; j < col; ++j) {
			m_double(i, j) = i*0.5 + j*1.1 + 0.2;
		}
	}
	std::cout << "a)\nm_double:" << m_double << '\n';

	//a)create matrix_row
	boost::numeric::ublas::matrix_row<boost::numeric::ublas::matrix<double>> m_row(m_double, 1);
	//print out
	std::cout << "matrix_row(1):" << m_row << '\n';
	
	//create matrix_column
	boost::numeric::ublas::matrix_column<boost::numeric::ublas::matrix<double>> m_col(m_double, 2);
	//print out
	std::cout << "matrix_col(2):" << m_col << '\n';
	
	//create matrix_range
	boost::numeric::ublas::matrix_range<boost::numeric::ublas::matrix<double>> m_range(m_double,
		boost::numeric::ublas::range(0, 1), boost::numeric::ublas::range(0, 2));
	//print out
	std::cout << "matrix_range((0,1),(0,2)):" << m_range << '\n';

	//create matrix_slice
	boost::numeric::ublas::matrix_slice<boost::numeric::ublas::matrix<double>> m_slice(m_double,
		boost::numeric::ublas::slice(0, 1, 2), boost::numeric::ublas::slice(0, 1, 2));
	std::cout << "matrix_slice((0,1,2),(0,1,2)):" << m_slice << '\n';

	//b)
	boost::numeric::ublas::matrix<double> m(3, 3);
	//assign values to m
	for (std::size_t i = 0; i < m.size1(); ++i) {
		for (std::size_t j = 0; j < m.size2(); ++j) {
			m(i, j) = i*3.1 + j + 0.3;
		}
	}
	//slice
	boost::numeric::ublas::matrix_slice<boost::numeric::ublas::matrix<double>> ms(m,
		boost::numeric::ublas::slice(0, 1, 3), boost::numeric::ublas::slice(0, 1, 3));
	
	//print out
	std::cout << "\nb)\nmatrix:" << m << '\n';
	std::cout << "matrix_slice((0,1,3),(0,1,3)):" << ms << '\n';

	return 0;

}