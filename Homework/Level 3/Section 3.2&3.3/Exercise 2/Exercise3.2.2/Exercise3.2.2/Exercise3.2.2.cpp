#include<iostream>
#include<thread>
#include<memory>
#include<random>
#include<chrono>
#include<array>
 //copied
struct X {
	double val;
	X() :val(0.0) {}
	void operator() () {
		std::cout << "An X " << val << std::endl;
	}
};
template<typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;

void Modify(PointerType& p, double newVal) {
	std::default_random_engine eng;
	std::uniform_int_distribution<int> distribution(100, 900);
	//wait for some time
	std::this_thread::sleep_for(std::chrono::milliseconds(distribution(eng)));
	//update state
	p->val = newVal;
	//print out current state
	std::cout << "\nnewVal=" << newVal << "; current state=" << p->val << std::endl;
}

int main() {
	//to create 100 threads
	const std::size_t N = 100;
	double start = 2.0;
	PointerType pt(new X);
	std::array<std::thread, N> arr;
	//b) fire 100 threads
	for (int i = 0; i < N; ++i) {
		start += 1.0;
		arr[i] = std::thread(&Modify, std::ref(pt), start);
	}
	//join all threads
	for (int i = 0; i < N; ++i) {
		arr[i].join();
	}

	//c) the printed result order is different for every compiling
	return 0;
}