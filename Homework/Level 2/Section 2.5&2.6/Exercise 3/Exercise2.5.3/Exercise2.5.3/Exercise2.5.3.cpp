#include<cmath>
#include<iostream>
#include<limits>
#include<boost/math/special_functions/next.hpp>
#include<exception>

//this function is to experiment wiht x given
template<typename T>
void experiment(T x, T y) {
	//set precision
	std::cout.precision(25);
	std::cout <<"x="<<x<<",y="<<y << ":\n";
	//display next representable value greater than x
	std::cout << "float_next: " << boost::math::float_next(x);
	
	//display next representable value smaller than x
	std::cout << "\nfloat_prior: " << boost::math::float_prior(x);
	
	//advance x by 5 ULP
	int advance = 5;
	std::cout << "\nfloat_advance: " << boost::math::float_advance(x, advance);
	
	//get number of gaps between x and y
	std::cout << "\nfloat_distance: " << boost::math::float_distance(x, y);

	//display next representable value of x in direction of y
	std::cout << "\nboost nextafter: " << boost::math::nextafter(x, y);
	std::cout << "\nstd nextafter: " << std::nextafter(x, y);
	std::cout << "\n";
}
int main() {
	//set precision
	std::cout.precision(25);
	// Number gaps/bits/ULP between 2 floating-point values a and b 
	// Returns a signed value indicating whether a < b 
	double a = 0.1; double b =  a + std::numeric_limits<double>::min(); 
	std::cout << boost::math::float_distance(a, b) << std::endl; 
	a = 1.0; b = 0.0; 
	std::cout << boost::math::float_distance(a, b) << std::endl;   
	//test the example given

	std::cout << '\n';
	//test other examples
	a = std::numeric_limits<double>::max();
	b = 10.0;
	try {
		experiment(a,b);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}

	a = -4.4;
	try {
		experiment(a, b);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}

	a = std::numeric_limits<double>::min();
	b = -0.9;
	try {
		experiment(b, a);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
	return 0;
}