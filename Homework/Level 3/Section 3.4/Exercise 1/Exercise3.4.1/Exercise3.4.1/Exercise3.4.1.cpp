#include<iostream>
#include<future>
//a)create func1 and func2
void func1() {
	std::cout << "in func1\n";
}
double func2(double a, double b) {
	std::cout << "in func2\n";
	return a + b;
}

int main() {
	//b) use async to launch func1 and func2
	double a = 1.1;
	double b = 2.1;
	//d) to use launch::async; no difference is observed
	//std::future<void> fut1(std::async(func1));
	//std::future<double> fut2(std::async(func2, a, b));
	std::future<void> fut1(std::async(std::launch::async,func1));
	std::future<double> fut2(std::async(std::launch::async, func2, a, b));
	//check validity before getting result
	std::cout << "before getting:\n";
	std::cout << "Is the fut1 valid? " << std::boolalpha << fut1.valid() << std::endl;
	std::cout << "Is the fut2 valid? " << std::boolalpha << fut2.valid() << std::endl;
	//get result
	std::cout << "\nget result\n";
	fut1.get();
	//std::cout << fut1.get() << std::endl;//not applicable
	std::cout << "fut2 val=" << fut2.get() << std::endl;
	//check validity after getting result
	std::cout << "after getting:\n";
	std::cout << "Is the fut1 valid? " << std::boolalpha << fut1.valid() << std::endl;
	std::cout << "Is the fut2 valid? " << std::boolalpha << fut2.valid() << std::endl;
	//c) If try to get result of future more than once, it will result in run-time error
	//fut1.get();
	//fut2.get();

	//e)use lazy evaluation
	std::future<double> fut3(std::async(std::launch::deferred, func2, a, b));
	std::cout << "\nbefore getting:\nIs fut3 valid? ";
	std::cout << std::boolalpha << fut3.valid() << std::endl;
	std::cout << "result=" << fut3.get() << std::endl;
	std::cout << "after getting:\nIs fut3 valid? ";
	std::cout << std::boolalpha << fut3.valid() << std::endl;

	return 0;
}