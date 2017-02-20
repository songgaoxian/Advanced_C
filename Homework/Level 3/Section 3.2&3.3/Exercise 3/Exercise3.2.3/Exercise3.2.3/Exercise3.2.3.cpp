#include"ActiveObject.h"
#include<chrono>
#include<system_error>
//to be used as thread function
void f1() {
	std::cout << "hello, c++\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	std::cout << "end of f1\n";
}

struct f2 {
	f2() { std::cout << "create f2\n"; }

	void operator() () {
		std::cout << "it is a f2 function object\n";
	}
};


int main() {
	//create a thread with f1
	std::thread t1(&f1);
	ActiveObject obj(std::move(t1));

	//create a thread with no associated function
	try {
		ActiveObject obj0(std::thread());
		//constructed or destructed not print out
	}
	catch (...) {
		std::cout << "error\n";
	}
	//no error printed out. It seems that create obj0 with a thread having no associated function cannot generate an exception
	
	//create thread function with function object
	f2 objf2;
	std::thread t2(&f2::operator(), objf2);
	ActiveObject obj2(std::move(t2));

	//create thread function with lambda function
	std::thread t3([]() {std::cout << "it is a lambda function\n"; });
	ActiveObject obj3(std::move(t3));

	return 0;
}