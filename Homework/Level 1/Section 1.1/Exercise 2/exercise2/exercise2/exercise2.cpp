#include<iostream>
#include<algorithm>
#include<vector>
#include<complex>
#include<functional>
#include<numeric>
#include<iterator>

auto MyMultiply = [](auto x, auto y) {return x*y; };
struct FOMultiply {
	template<typename T>
	T operator()(const T& x, const T& y) { return x*y; }
};
template<typename T>
T MyMultiply2(const T& x, const T& y) { return x*y; };

auto greaterThan3 = [](int input)->bool {
	if (input > 3)
		return true;
	else
		return false;
};

int main() {
	std::vector<int> vec{ 1,2,3,4,5 };
	int initVal = 1;
	int accLamda = std::accumulate(vec.begin(), vec.end(), initVal, MyMultiply);
	int acc2 = std::accumulate(vec.begin(), vec.end(), initVal, std::multiplies<int>());
	int accA = std::accumulate(vec.begin(), vec.end(), initVal, FOMultiply());
	std::cout << "Lamda: " << accLamda << std::endl;
	std::cout << "Algorithm: " << acc2 << std::endl;
	std::cout << "Function Object: " << accA << std::endl;

	using Complex = std::complex<double>;
	std::vector<Complex> complexArray{ Complex(1.0, 1.0), Complex(2.0, 2.0) };
	Complex initCVal(1.0, 1.0);
	auto acc6C = accumulate(complexArray.begin(), complexArray.end(), initCVal, FOMultiply());
	Complex acc7C = accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply2<Complex>);
	Complex acc8C = accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply);
	std::cout << "For complex: \n";
	std::cout << "Sum 6, complex numbers: " << acc6C << std::endl;
	std::cout << "using free function: " << acc7C << std::endl;
	std::cout << "using lamda function: " << acc8C << std::endl;
	//a) The algorithm can also be used with complex numbers and we can use function objects to multiply elements of array of complex numbers
	int accb1 = initVal;
	std::for_each(vec.begin(), vec.end(),
		[&accb1](int input) {
		accb1 = MyMultiply(accb1, input);
		return accb1;
	});
	std::cout << "Simulated accumulation for int: " << accb1 << std::endl;
	Complex accb2 = initCVal;
	std::for_each(complexArray.begin(), complexArray.end(),
		[&accb2](Complex input) {
		accb2 = MyMultiply(accb2, input);
		return accb2;
	});
	std::cout << "Simulated accumulation for complex numbers: " << accb2 << std::endl;
	//b)
	std::cout << "c: ";

	std::vector<int> tobeModified = vec;
	auto fc = [tobeModified]()mutable {
		std::remove_copy_if(tobeModified.begin(), tobeModified.end(), std::ostream_iterator<int>(std::cout, ", "),
			greaterThan3);
	};
	fc();
	//c
	return 0;
}