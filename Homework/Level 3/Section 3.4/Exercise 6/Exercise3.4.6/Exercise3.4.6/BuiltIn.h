#ifndef Double_H
#define Double_H
#include<iostream>
#include<vector>
#include<array>
#include<future>
#include<thread>
#include<chrono>
template<typename T>
T F1BuiltIn(T a) { return a * 2; }
template<typename T>
T F2BuiltIn(T a) { return a * 3; }
template<typename T>
T F3BuiltIn(T c) { return c - 5; }
template<typename T>
T F4BuiltIn(T b, T d) { return b + d; }

//a)single-thread implementation
template<typename T>
T singleThreadBuiltIn(T a) {
	T b = F1BuiltIn<T>(a);
	T c = F2BuiltIn<T>(a);
	T d = F3BuiltIn<T>(c);
	T f = F4BuiltIn<T>(b, d);
	return f;
}

//b) use async and future
template<typename T>
T asyncfutureBuiltIn(T a) {
	std::future<T> b = std::async(F1BuiltIn<T>, a);
	T c = F2BuiltIn<T>(a);
	T d = F3BuiltIn<T>(c);
	T f = F4BuiltIn<T>(b.get(), d);
	return f;
}

//c) using promises
template<typename T>
void Getb(T a, std::promise<T> p) {
	T b = F1BuiltIn(a);
	p.set_value(b);
}

template<typename T>
T promiseBuiltIn(T a) {
	std::promise<T> sharedData;
	std::shared_future<T> fut1 = sharedData.get_future();
	//get the value of b
	Getb<T>(a, std::move(sharedData));
    T c = F2BuiltIn<T>(a);
	T d = F3BuiltIn<T>(c);
	T f = F4BuiltIn<T>(fut1.get(), d);
	return f;
}

//d) using packaged tast
template<typename T>
T packagedtaskBuiltIn(T a) {
	std::packaged_task<T(T)> myTask1(F1BuiltIn<T>);
	std::packaged_task<T(T)> myTask2(F2BuiltIn<T>);
	auto fut1 = myTask1.get_future();
	auto fut2 = myTask2.get_future();
	//start the first two tasks
	myTask1(a);
	myTask2(a);
	//wait for task to end and process result
	T b = fut1.get();
	T c = fut2.get();
	T d = F3BuiltIn(c);
	T f = F4BuiltIn(b, d);
	return f;
}
#endif
