#ifndef Client_H
#define Client_H
#include<algorithm>
#include<list>
#include<iostream>

template<typename T> struct Storage {
	typedef std::list<T, std::allocator<T>> type;
};


template<typename T>
class Client {
private:
	typename Storage<T>::type data;
public:
	Client(int n, const T& val): data(n,val){}
	void print() const {
		std::for_each(data.begin(), data.end(), [](const T& n) {std::cout << n << ","; });
		std::cout << '\n';
	}
};

//recreate Client as newClient
template<typename T>
using newStorage = std::list<T, std::allocator<T>>;

template<typename T>
class newClient {
private:
	newStorage<T> data;
public:
	newClient(int n, const T& val):data(n,val){}
	void print() const {
		std::for_each(data.begin(), data.end(), [](const T& n) {std::cout << n << ","; });
		std::cout << '\n';
	}
};



#endif
