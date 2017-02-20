//Exercise4.10.1
//
//exercise to operate dense vectors
//written on 2016/6/24

#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<complex>
#include<iostream>
#include<algorithm>
using c_double = std::complex<double>;

int main() {
	//to be used to create dense vectors
	std::size_t N = 10;
	double val = 1.1;
	//a)create a vector v1 of size N
	std::cout << "a)\n";
	//boost::numeric::ublas::vector<double> v1(N);//double version
	boost::numeric::ublas::vector<c_double> v1(N);//complex double version
	
	
	//access using () to store data
	for (int i = 0; i < N; ++i) {
		v1(i) = c_double(val,val+0.1);
		val += 0.1;
	}

	//access using [] to print data
	std::cout << "Contents of v1:\n";
	for (int i = 0; i < N; ++i) {
		std::cout << v1[i] << " ";
	}

	//b)create vector v2 of same size with v1
	//boost::numeric::ublas::vector<double> v2(v1.size());//double version
	boost::numeric::ublas::vector<c_double> v2(v1.size());//complex<double> version
	for (int i = 0; i < v2.size(); ++i) {
		v2[i] = c_double((double)i*2.0,double(i));
	}
	std::cout << "\n\nb)\nv2:" << v2 << '\n';
	//compute v1+=v2
	v1 += v2;
	std::cout << "after v1+=v2, v1:" << v1 << '\n';
	//compute v1*=2.5;
	v1 *= 2.5;
	std::cout << "after v1*=2.5, v1:" << v1 << '\n';
	//compute v1-=v2;
	v1 -= v2;
	std::cout << "after v1-=v2, v1:" << v1 << '\n';

	//c)use transform and multiply
	//boost::numeric::ublas::vector<double> v3(v1.size());//double version
	boost::numeric::ublas::vector<c_double> v3(v1.size());//complex<double> version
	//apply transform
	//std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<double>());//double version
	std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<c_double>());//complex<double> version
	std::cout << "\nc)\nv3:" << v3 << '\n';

	//d)create scalar vector
	//boost::numeric::ublas::scalar_vector<double> s_vector(100, 5.0);//double version
	boost::numeric::ublas::scalar_vector<c_double> s_vector(100, c_double(5, 0));//complex<double> version
	std::cout << "\nd)\ns_vector:" << s_vector << '\n';

	return 0;

}
