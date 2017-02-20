#include<algorithm>
#include<string>
#include<iostream>
#include<vector>
#include<iterator>
#include<ctime>
#include<ratio>
#include<chrono>
class TestObject {
public:
	TestObject() { std::cout << "default constructor\n"; }
	TestObject(const TestObject& src) { std::cout << "copy constructor\n"; }
	TestObject operator=(const TestObject& src) { std::cout << "assign\n"; return *this; }
	~TestObject() { std::cout << "destructor\n"; }
};
template<typename T>
void SwapCopyStyle(T& a, T& b) {
	T tmp(a);
	a = b;
	b = tmp;
}
template<typename T>
void SwapMoveStyle(T& a, T& b) {
	T tmp;
	tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);
}


int main() {
	std::string source = "hello, world";
	std::string target;
	std::cout << "Before move\n";
	std::cout << "source: " << source << std::endl;
	std::cout << "target: " << target << std::endl;
	target = std::move(source);
	std::cout << "After move\n";
	std::cout << "source: " << source << std::endl;
	std::cout << "target: " << target << std::endl;
	//a

	std::vector<double> source1;
	std::vector<double> target1;
	std::vector<double> source2;
	std::vector<double> source3;
	std::vector<double> target2;
	for (int i = 0; i < 5000; i++) {
		source2.push_back(i*2.1);
	}
	for (int i = 0; i < 4; i++)
		source1.push_back(i*1.1);
	std::cout << "Before move:\n";
	std::cout << "source1 vector: ";
	for (auto it = source1.begin(); it != source1.end(); it++) std::cout << *it << ", ";
	std::cout << "\ntarget1 vector: ";
	for (auto it = target1.begin(); it != target1.end(); it++) std::cout << *it << ", ";
	std::cout << std::endl;
	target1 = std::move(source1);
	std::cout << "After move:\n";
	std::cout << "source1 vector: ";
	for (auto it = source1.begin(); it != source1.end(); it++) std::cout << *it << ", ";
	std::cout << "\ntarget1 vector: ";
	for (auto it = target1.begin(); it != target1.end(); it++) std::cout << *it << ", ";
	std::cout << std::endl;
	
	for (int i = 0; i < 90000; i++) source2.push_back(i*1.1);
	//compare time
	source3 = source2;
	target2 = std::move(source2); 
	//b)
	TestObject t1;
	TestObject t2;
	SwapCopyStyle<TestObject>(t1, t2); //copy constructor is called 3 times and assignment operator is called twice
	std::vector<int> vec1;
	std::vector<int> vec2;
	for (int i = 0; i < 900000; i++) { vec1.push_back(0); vec2.push_back(1); }
	using namespace std::chrono;
	steady_clock::time_point time1 = steady_clock::now();
	SwapCopyStyle<std::vector<int>>(vec1, vec2);
	steady_clock::time_point time2 = steady_clock::now();
	SwapMoveStyle<std::vector<int>>(vec1, vec2);
	steady_clock::time_point time3 = steady_clock::now();
	duration<double> timecopy = duration_cast<duration<double>>(time2 - time1);
	duration<double> timemove = duration_cast<duration<double>>(time3 - time2);
	std::cout << "Copy takes " << timecopy.count() << "\n";
	std::cout << "Move takes " << timemove.count() << "\n";
	//c

	return 0;
}