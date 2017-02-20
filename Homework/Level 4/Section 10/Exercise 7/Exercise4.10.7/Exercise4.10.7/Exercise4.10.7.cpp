//Exeercise4.10.7
//
//explore arithmetic operations on vector and matrix
//written on 2016/6/25

#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\vector.hpp>
#include<boost\numeric\ublas\io.hpp>
#include<iostream>
#include<complex>

using c_double = std::complex<double>;

int main() {
	std::size_t n = 3;
	//using value_type = double;
	//use c_double
	using value_type = c_double;
	//create vectors
	boost::numeric::ublas::vector<value_type> vd1(n), vd2(n);
	//assign values to vd1 and vd2
	for (std::size_t i = 0; i < n; ++i) {
		vd1[i] = i*3.1 + 0.5;
		vd2[i] = i*2.1 + 1.2;
	}
	//compute inner product
	value_type inner_p = boost::numeric::ublas::inner_prod(vd1, vd2);
	//compute outer product
	auto outer_p = boost::numeric::ublas::outer_prod(vd1, vd2);
	//print out 
	std::cout << "vector vd1:" << vd1 << '\n';
	std::cout << "vector vd2:" << vd2 << '\n';
	std::cout << "inner product of vd1 and vd2:" << inner_p << '\n';
	std::cout << "outer product of vd1 and vd2:" << outer_p << '\n';
	std::cout << '\n';

	//conduct add and subtract
	boost::numeric::ublas::vector<value_type> add_vd = vd1 + vd2;
	boost::numeric::ublas::vector<value_type> sub_vd = vd1 - vd2;
	//print out
	std::cout << "vd1+vd2=" << add_vd << '\n';
	std::cout << "vd1-vd2=" << sub_vd << '\n';
	std::cout << '\n';

	//calculate Euclidean(l2), l1 and max norm
	value_type L2_norm = boost::numeric::ublas::norm_2(vd1);
	value_type L1_norm = boost::numeric::ublas::norm_1(vd1);
	value_type max_norm = boost::numeric::ublas::norm_inf(vd1);
	//print out
	std::cout << "L1 norm of vd1=" << L1_norm << '\n';
	std::cout << "L2(Euclidean) norm of vd1=" << L2_norm << '\n';
	std::cout << "max norm of vd1=" << max_norm << "\n\n";

	//create matrix
	std::size_t row = 3, col = 3;
	boost::numeric::ublas::matrix<value_type> m(row, col);
	//assign values to m
	for (std::size_t i = 0; i < row; ++i) {
		for (std::size_t j = 0; j < col; ++j) {
			m(i, j) = i*1.1 + j + 0.5;
		}
	}
	//calculate L1 and max norm of m
	value_type L1_m = boost::numeric::ublas::norm_1(m);
	value_type max_m = boost::numeric::ublas::norm_inf(m);
	//print out
	std::cout << "matrix m=" << m << '\n';
	std::cout << "L1 norm of m=" << L1_m << '\n';
	std::cout << "max norm of m=" << max_m << "\n\n";

	//conduct product of matrix and vector
	auto matrix_vector = boost::numeric::ublas::prod(m, vd1);
	auto vector_matrix = boost::numeric::ublas::prod(vd1, m);
	//print out
	std::cout << "matrix*vector=" << matrix_vector << '\n';
	std::cout << "vector*matrix=" << vector_matrix << '\n';


	return 0;

}