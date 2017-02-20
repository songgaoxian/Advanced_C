#include<iostream>
#include<functional>
#include<numeric>
#include<vector>

template<typename T>
using FunctionType = std::function<T(const T& t)>;

FunctionType<double> f(const double& t) {
	return [=](const double& t) {
		return t*t;
	};
}

template<typename T>
void print(const FunctionType<T>& g, T t) {
	std::cout << g(t) << "\n";
}

double Sum(FunctionType<double> g, const double& y,const double& x) {
	return g(x) + g(y);
} //free function

struct SumObj {
	double d;
	SumObj(double input) :d(input) {}
	double operator() (const double& basis, FunctionType<double> g) {
		return (g(d) + g(basis));
	}
};

auto SumLamda = [&](const double& x, const double& y)->double 
{
	auto g = f(x);
	auto h = f(y);
	return g(x)+h(y);
};

int main() {
	FunctionType<double> f1 = f(10.0);
	print<double>(f1, 10.0);
	print<double>(f1, 20.0);
	double thesum = Sum(f1, 9.0, 1.0);
	std::cout << "Sum: " << thesum << "\n";
	SumObj objSum(5.0);
	double theobjsum=objSum(2.0, f1);
	std::cout << "Obj Sum: " << theobjsum << "\n";
	double ini = 2.0;
	std::vector<double> vec { 1.0,2.0,3.0 };
	double result = std::accumulate(vec.begin(), vec.end(), ini, SumLamda);
	std::cout << "accumulate: " << result << "\n";
	return 0;
}
