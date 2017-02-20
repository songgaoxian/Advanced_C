#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>

using ScalarFunction = std::function<double(const double&)>;

//implement bind1st
template<typename T>
std::function<T(const T&)> bind1st
(const std::function<T(const T& x, const T& y)>& f, const T& x_) {
	//return the function by binding x_ to first argument
	return [=](const T& y) {
		return f(x_, y);
	};
}
//implement bind2nd
template<typename T>
std::function<T(const T&)> bind2nd
(const std::function<T(const T& x, const T& y)>& f, const T& y_) {
	//return the function by binding y_ to second argument
	return [=](const T& x) {
		return f(x, y_);
	};
}

int main() {
	//test bind2nd and bind1st
	//declare and initialize variables 
	auto fxy = [](double x, double y) {return 2 * x + y; };
	double yval = 10.0;
	//apply bind2nd
	ScalarFunction fx = bind2nd<double>(fxy, yval);
	//print out fx(3.0)
	std::cout << fx(3.0) << std::endl;

	//test new bind code on STL algorithm
	std::vector<double> vec(10, 2.0);
	std::transform(vec.begin(), vec.end(), vec.begin(), fx);
	for (auto i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << ",";
	}

	std::cout << "\nTest bind1st\n";
	//test bind1st
	double xval = 55.0;
	ScalarFunction fy = bind1st<double>(fxy, xval);
	//print out fy(5.0)
	std::cout << fy(5.0) << std::endl;
	//end testing

	return 0;

}