#include<iostream>
#include<vector>
#include<array>

int main() {
	//for part a)
	//declare and initialize variables
	int size = 4; double val = 2.71;
	std::vector<double> data(size, val);
	//modify the code of lambda function fun by moving data to local variable data
	auto fun1 = [data = std::move(data)]() mutable{
		for (std::size_t i = 0; i < data.size(); ++i) {
			data[i] = 3.14; std::cout << data[i] << ", ";
		}
		std::cout << "\n";
	};
	//run fun1()
	fun1();
	//print the current size of data
	std::cout << "size of data: " << data.size() << std::endl;
	//try to print the content of data if exists
	for (std::size_t i = 0; i < data.size(); i++) {
		data[i] = 3.14; std::cout << data[i] << ":";
	}
	//end of a)

	//for b)
	std::cout << "start of part b:\n";
	int x = 1'000'000; //it is a digit separator
	auto fun4 = [&r = x]() {
		r *= 2;
		std::cout << "\nr: " << r;
	};
	fun4(); //print out 2000000
			//end of b)

			//for c)
	std::cout << '\n';
	//declare and initialize variables to use
	int size2 = 3; double val2 = 1.41;
	std::vector<double> data2(size2, val2);
	std::array<double, 3> data3{ 1.2,2.4,4.7 };
	//modify fun3 by using init capture: move data2 to arr, move data3 to arr2
	//arr and arr2 are local variables
	auto fun5 = [arr = std::move(data2), arr2 = std::move(data3)]()mutable{
		//print content of arr
		for (std::size_t i = 0; i < arr.size(); ++i) {
			arr[i] = 3.14; std::cout << arr[i] << "/";
		}
		std::cout << '\n';
		//print content of arr2
		for (std::size_t i = 0; i < arr2.size(); ++i) {
			arr2[i] = 2.71; std::cout << arr2[i] << "/";
		}
	};
	//run fun5
	fun5();
	//check the size of data2 and data3
	if (0 == data2.size() || 0 == data3.size()) {
		std::cout << "\nDouble arrays have no elements, OK\n";
	}
	else {
		//if not 0, display their contents
		std::cout << "\n Ouch!\n";
		for (std::size_t i = 0; i < data2.size(); ++i) {
			std::cout << data2[i] << "^";
		}
		for (std::size_t i = 0; i < data3.size(); ++i) {
			std::cout << data3[i] << "^";
		}
	}
	//end of c)

	return 0;
}