#include<iostream>
#include<future>
#include<chrono>
#include<thread>

int stop = 0;

int GetNumber() {
	std::this_thread::sleep_for(std::chrono::milliseconds(600));
	std::cout << "GetNumber is ready to return\n";
	return 20;
}

int infinite() {
	while (true) {
		std::cout << "*";
		if (stop != 0)
			break;
	}
	return 0;
}

int main() {
	//a)
	//default instance
	std::shared_future<void> default_f;
	//share the same state as the following
	std::shared_future<int> f1(std::async(GetNumber));
	std::shared_future<int> f2(f1);
	//normal future
	std::future<int> f3(std::async(GetNumber));
	//transfer to shared future from normal future
	std::shared_future<int> f4 = f3.share();
	//transfer to shared future from a shared future
	std::shared_future<int> f5 = f4;
	//b)
	//check wait for
	f1.wait_for(std::chrono::milliseconds(300));
	std::cout << "f1 wait no more than 300 milliseconds\n";
	//check wait until
	f2.wait_until(std::chrono::system_clock::now() + std::chrono::milliseconds(340));
	std::cout << "f2 wait no more than 340 milliseconds\n";
	//check wait
	f4.wait();
	std::cout << "f4 waits\n";
	//check get
	std::cout << "f5 is " << f5.get() << std::endl;
	//check valid
	std::cout << "Is f5 valid? " << std::boolalpha << f5.valid() << std::endl;

	//c) get twice
	std::cout << "f5 is " << f5.get() << std::endl; //compile and run appropriately
	//d)
	std::shared_future<int> f6(std::async(infinite));
	std::cout << "f6 created for the inifitePrint\n";
	f6.wait_for(std::chrono::milliseconds(100));
	stop = 1;
	std::cout << "f6 wait finished\n";
	std::cout << "f7 created for the inifitePrint\n";
	stop = 0;
	std::shared_future<int> f7(std::async(infinite));
	f7.wait_until(std::chrono::system_clock::now()+std::chrono::milliseconds(100));
	stop = 1;
	std::cout << "f7 wait finished\n";


	return 0;

}