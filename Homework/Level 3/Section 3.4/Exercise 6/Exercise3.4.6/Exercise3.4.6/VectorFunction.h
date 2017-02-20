#ifndef VectorFunction_H
#define VectorFunction_H
#include<iostream>
#include<vector>
#include<array>
#include<future>
#include<thread>
#include<chrono>
template<typename T>
std::vector<T> F1Vector(std::vector<T> a) {
	std::vector<T> b = a;
	for (auto it = b.begin(); it != b.end(); ++it)
		*it /= 2;
	return b;
}
template<typename T>
std::vector<T> F2Vector(std::vector<T> a) {
	std::vector<T> c(a);
	for (auto it = c.begin(); it != c.end(); ++it)
		*it *= 3;
	return c;
}
template<typename T>
std::vector<T> F3Vector(std::vector<T> c) {
	std::vector<T> d(c);
	for (auto it = d.begin(); it != d.end(); ++it)
		*it += 3;
	return d;
}
template<typename T>
std::vector<T> F4Vector(std::vector<T> b, std::vector<T> d) {
	std::vector<T> f;
	for (int i = 0; i < b.size(); ++i) {
		f.push_back(b[i] + d[i]);
	}
	return f;
}

//a) single-thread implementation
template<typename T>
std::vector<T> singleThreadVector(std::vector<T> a) {
	std::vector<T> b = F1Vector<T>(a);
	std::vector<T> c = F2Vector<T>(a);
	std::vector<T> d = F3Vector<T>(c);
	return F4Vector<T>(b, d);
}
//b) use async and future
template<typename T>
std::vector<T> asyncfutureVector(std::vector<T> a) {
	std::future<std::vector<T>> b = std::async(F1Vector<T>, a);
	std::vector<T> c = F2Vector<T>(a);
	std::vector<T> d = F3Vector<T>(c);
	return F4Vector<T>(b.get(), d);
}
//c)use promise
template<typename T>
void Getb(std::vector<T> a, std::promise<std::vector<T>> p) {
	std::vector<T> b = F1Vector<T>(a);
	p.set_value(b);
}
template<typename T>
std::vector<T> promiseVector(std::vector<T> a) {
	std::promise<std::vector<T>> sharedData;
	std::shared_future<std::vector<T>> fut1 = sharedData.get_future();
	Getb<T>(a,std::move(sharedData));
	std::vector<T> c = F2Vector<T>(a);
	std::vector<T> d = F3Vector<T>(c);
	return F4Vector(fut1.get(), d);
}
//d)use packaged tasks
template<typename T>
std::vector<T> packagedVector(std::vector<T> a) {
	std::packaged_task<std::vector<T>(std::vector<T>)> task1(F1Vector<T>);
	std::packaged_task<std::vector<T>(std::vector<T>)> task2(F2Vector<T>);
	std::future<std::vector<T>> b = task1.get_future();
	std::future<std::vector<T>> c = task2.get_future();
	//start tasks
	task1(a);
	task2(a);
	std::vector<T> d = F3Vector<T>(c.get());
	return F4Vector<T>(b.get(), d);
}

#endif
