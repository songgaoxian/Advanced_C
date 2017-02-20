#include<iostream>
#include<atomic>
#include<thread>
#include<memory>
//copied
struct X {
	double val;
	X() :val(0.0) {}
	void operator()() {
		std::cout << "An X " << val << std::endl;
	}
};

template<typename T>
using GenericPointerType = std::shared_ptr<T>;

using PointerType = GenericPointerType<X>;

int main() {
	//a) create an instance x of PointerType
	PointerType x(new X);
	x->val = 3.3;
	std::cout << "use count of x: " << x.use_count() << std::endl;
	//b) create an instance x2 and store it value in x
	PointerType x2;
	std::atomic_store_explicit(&x2, x,std::memory_order_seq_cst);
	std::cout << "use count of x2: " << x2.use_count() << std::endl;
	//c) create instance x3 and exchange it with both x and x2
	PointerType x3;
	std::atomic_exchange_explicit(&x3, x,std::memory_order_seq_cst);
	std::cout << "use count of x3: " << x3.use_count() << std::endl;
	std::atomic_exchange_explicit(&x3, x2,std::memory_order_seq_cst);
	std::cout << "use count of x3: " << x3.use_count() << std::endl;
	//e) shared_ptr is not atomic. If multiple threads access same shared_ptr without synchronization or overloading atomic access functions, a data race may occur
	//f) check if lock free
	std::cout << "are shared pointers lock free?\n";
	std::cout << std::boolalpha << std::atomic_is_lock_free(&x3);
	return 0;
}

