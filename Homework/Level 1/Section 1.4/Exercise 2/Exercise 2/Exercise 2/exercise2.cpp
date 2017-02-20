#include<iostream>
#include<functional>
#include<numeric>
using namespace std;
using namespace std::placeholders;




double freeFunction3(double x, double y, double z) {
	return x + y+z;
}
function<double(double, double, double)> f3(function<double(double, double, double)> input) {
	return input;
}
function<double(double, double)> f2(function<double(double x, double y, double z)> input, double x_) {
	return [=](double y,double z) {
		return input(x_, y, z);
	};
}
function<double(double)> f1(function<double(double, double, double)> input, double x_, double y_) {
	return [=](double z) {
		return input(x_, y_, z);
	};
}
function<double()>f0(function<double(double, double, double)> input, double x_, double y_, double z_) {
	return [=]() {
		return input(x_, y_, z_);
	};
}
int main() {
	double x_ = 1.0;
	double y_ = 2.0;
	double z_ = 3.0;
	auto defined3 = f3(freeFunction3);
	auto defined2 = f2(freeFunction3, x_);
	auto defined1 = f1(freeFunction3, x_, y_);
	auto defined0 = f0(freeFunction3, x_, y_, z_);

	auto binded3 = defined3;
	auto binded2 = std::bind(freeFunction3,x_,_1,_2);
	auto binded1 = std::bind(freeFunction3,x_, y_,_1);
	auto binded0 = std::bind(freeFunction3,x_,y_, z_);
	
	double a = 10.1;
	double b = 66.1;
	double c = 73.1;
	cout << "defined 3: " << defined3(a, b, c) << endl;
	cout << "defined 2: " << defined2(a, b) << endl;
	cout << "defined 1: " << defined1(c) << endl;
	cout << "defined 0: " << defined0() << endl;
	cout << "binded 3: " << binded3(a, b, c) << endl;
    cout << "binded 2: " <<binded2(a,b) << endl;
	cout << "binded 1: " << binded1(c) << endl;
	cout << "binded 0: " << binded0() << endl;
	return 0;

}
