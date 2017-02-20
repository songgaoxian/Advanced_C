#include<iostream>
#include<functional>
#include<future>
#include<thread>

void print(std::future<double>& fut) {
	std::cout << "Future val is " << fut.get() << std::endl;
}

int main() {
	//a) create default promise
	std::promise<int> default_promise;
	//empty shared state
	std::promise<int> empty_p();
	int val = 2;
	default_promise.set_value(val);
	//move constructed promise
	std::promise<int> move_p(std::move(default_promise));

	//b)
	double dval = 3.4;
	std::promise<double> dpromise;
	std::future<double> fut = dpromise.get_future();
	std::thread myThread(&print, std::ref(fut));
	//d)set val of shared data
	dpromise.set_value(dval);
	myThread.join();
	return 0;
}