#include<iostream>
#include<thread>
#include<string>
#include<functional>
#include<chrono>
#include<vector>
#include<mutex>
#include<system_error>

std::mutex p_mutex;
std::timed_mutex t_mutex;

int counter = 0; //counter to be incremented
//function to increate counter by multiple threads
void increment() {
	/*
	//c) try to lock mutex
	std::unique_lock<std::mutex> u1(p_mutex); //include this line will generate error
	try {
		errno = 0;
		std::unique_lock<std::mutex> u(p_mutex,std::defer_lock);
		//std::unique_lock<std::mutex> u; //generate error
		u.lock();
		counter++;
	}
	catch (std::system_error& e) {
		if (e.code() == std::errc::operation_not_permitted) {
			std::cout << "no associated mutex\n";
		}
		else if (e.code() == std::errc::device_or_resource_busy) {
			std::cout << "mutex already locked\n";
		}
		else {
			std::cout << e.what() << std::endl;
		}
	}
	*/
	/*
	//d) apply try_lock_for
	//std::unique_lock<std::timed_mutex> t(t_mutex); //result in infinite loop to print out w	
	try {
		errno = 0;
		//std::unique_lock<std::timed_mutex> tlck(t_mutex, std::defer_lock);
		std::unique_lock<std::timed_mutex> tlck; //generate error
		while (!tlck.try_lock_for(std::chrono::milliseconds(30))) {
			std::cout << 'w'; //means waiting
		}
		counter++;
	}
	catch (std::system_error& e) {
		std::cout << std::endl;
		if (e.code() == std::errc::operation_not_permitted) {
			std::cout << "no associated mutex\n";
		}
		else {
			std::cout << e.what() << std::endl;
		}
	}*/
	/*
	//e)apply unlock
	try {
		std::unique_lock<std::mutex> ulock(p_mutex);
		counter++;
		ulock.unlock(); //include this line will result in error
		ulock.unlock();
	}
	catch (std::system_error& e) {
		std::cout << std::endl;
		if (e.code() == std::errc::operation_not_permitted) {
			std::cout << "unlock more than once\n";
		}
		else {
			std::cout << e.what() << std::endl;
		}
	}
	*/
	/*
	//f) apply try_lock_until
	//std::unique_lock<std::timed_mutex> t(t_mutex); //result in infinite loop to print out w	
	try {
		std::unique_lock<std::timed_mutex> until(t_mutex, std::defer_lock);
		//std::unique_lock<std::timed_mutex> until; 
		while (!until.try_lock_until(std::chrono::system_clock::now()+std::chrono::milliseconds(30))) {
			std::cout << 'w'; //means waiting
		}
		counter++;
	}
	catch (std::system_error& e) {
		std::cout << std::endl;
		if (e.code() == std::errc::operation_not_permitted) {
			std::cout << "no associated mutex\n";
		}
		else {
			std::cout << e.what() << std::endl;
		}
	}
	*/
	//g) mutex is unlocked automatically when it goes out of scope
	{
		std::unique_lock<std::mutex> lock(p_mutex);
		counter++;
		try {
			//if p_mutex is unlocked, there will be no error. Otherwise, exception generated
			std::unique_lock<std::mutex> lock1(p_mutex);
			std::cout << "p_mutex has been unlocked inside the block\n";
		}
		catch (std::system_error& e) {
			std::cout << e.what() << std::endl;
			std::cout << "p_mutex has not been unlocked inside the block\n";
		}
	}

	try {
		//if p_mutex is unlocked, there will be no error. Otherwise, exception generated
		std::unique_lock<std::mutex> lock2(p_mutex);
		std::cout << "p_mutex has been unlocked outside the block\n";
	}
	catch (std::system_error& e) {
		std::cout << e.what() << std::endl;
		std::cout << "p_mutex has not been unlocked outside the block\n";
	}
	
}

//copy code from 3.1.2
void Iprint(const std::string& s, int count) {
	std::lock_guard<std::mutex> locker(p_mutex);
	std::cout << "print " << count << " times\n";
	for (int i = 0; i < count; ++i)
		std::cout << s << std::endl;
}
void print1(const std::string& s, int count) {
	std::cout << "\nIn print1: ";
	std::cout << std::this_thread::get_id() << std::endl;
	//measure the number of times trying to lock mutex
	int failure = 0;
	while (true) {
		//if try_lock true, exit the loop
		if (p_mutex.try_lock()) {
			p_mutex.unlock();
			break;
		}
		else {
			failure++;
		}
	}
	Iprint(s, count);
	std::cout << "for print1, it takes " << failure << " times to acquire the lock\n";
}
auto print2 = [](const std::string& s, int count) {
	std::cout << "\nIn print2: ";
	std::cout << std::this_thread::get_id() << std::endl;
	//measure the number of times trying to lock mutex
	int failure = 0;
	while (true) {
		//if try_lock true, exit the loop
		if (p_mutex.try_lock()) {
			p_mutex.unlock();
			break;
		}
		else {
			failure++;
		}
	}
	Iprint(s, count);
	std::cout << "for print2, it takes " << failure << " times to acquire the lock\n";
};
struct print3 {
	print3() {}
	void operator()(const std::string& s, int count) {
		std::cout << "\nIn print3: ";
		std::cout << std::this_thread::get_id() << std::endl;
		//measure the number of times trying to lock mutex
		int failure = 0;
		while (true) {
			//if try_lock true, exit the loop
			if (p_mutex.try_lock()) {
				p_mutex.unlock();
				break;
			}
			else {
				failure++;
			}
		}
		Iprint(s, count);
		std::cout << "for print3, it takes " << failure << " times to acquire the lock\n";
	}
};
class print4 {
public:
	print4() {}
	static void display(const std::string& s, int count) {
		std::cout << "\nIn print4 static member: ";
		std::cout << std::this_thread::get_id() << std::endl;
		//measure the number of times trying to lock mutex
		int failure = 0;
		while (true) {
			//if try_lock true, exit the loop
			if (p_mutex.try_lock()) {
				p_mutex.unlock();
				break;
			}
			else {
				failure++;
			}
		}
		Iprint(s, count);
		std::cout << "for print4 static member function, it takes " << failure << " times to acquire the lock\n";
	}
	void display2(const std::string& s, int count) {
		std::cout << "\nIn print4 member: ";
		std::cout << std::this_thread::get_id() << std::endl;
		//measure the number of times trying to lock mutex
		int failure = 0;
		while (true) {
			//if try_lock true, exit the loop
			if (p_mutex.try_lock()) {
				p_mutex.unlock();
				break;
			}
			else {
				failure++;
			}
		}
		Iprint(s, count);
		std::cout << "for print4 binded member function, it takes " << failure << " times to acquire the lock\n";
	}
};

int main() {
	//increment counter
	std::thread incre1(&increment);
	std::thread incre2(&increment);
	std::thread incre3(&increment);
	std::thread incre4(&increment);
	incre1.join();
	incre2.join();
	incre3.join();
	incre4.join();
	//check result of counter
	std::cout << "counter = " << counter << std::endl;

	//copy codes from exercise 3.1.2
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::string s("glad to know not alone");
	int count = 5;
	std::thread t1(&print1, std::ref(s), count);
	t1.detach();
	std::cout << "\nt1 thread id: " << t1.get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::thread t2([](const std::string& s, int count) {
		std::cout << "\nIn lambda: ";
		//measure the number of times trying to lock mutex
		int failure = 0;
		while (true) {
			//if try_lock true, exit the loop
			if (p_mutex.try_lock()) {
				p_mutex.unlock();
				break;
			}
			else {
				failure++;
			}
		}
		Iprint(s, count);
		std::cout << "for lambda, it takes " << failure << " times to acquire the lock\n";
	}, std::ref(s), count);
	std::cout << "\nt2 thread id: " << t2.get_id() << std::endl;
	std::thread tt2(print2, std::ref(s), count);
	std::cout << "\ntt2 thread id: " << tt2.get_id() << std::endl;
	print3 p3;
	std::thread t3(&print3::operator(), p3, std::ref(s), count);
	//print t3 thread id e)
	std::cout << "\nt3 thread id: " << t3.get_id() << std::endl;
	std::thread t4(&print4::display, std::ref(s), count);
	std::cout << "\nt4 thread id: " << t4.get_id() << std::endl;
	print4 p4;
	std::function<void(std::string&, int)> f4 = std::bind(&print4::display2, p4, std::placeholders::_1, std::placeholders::_2);
	std::thread t5(f4, std::ref(s),count);
	std::cout << "\nt5 thread id: " << t5.get_id() << std::endl;
	if (t2.joinable()) {
		t2.join(); //finished executing
		std::cout << "\nt2 joined\n";
	}
	if (tt2.joinable()) {
		tt2.join();//finished executing
		std::cout << "\ntt2 joined\n";
	}
	if (t3.joinable()) {
		t3.join(); //finished executing
		std::cout << "\nt3 joined\n";
	}
	if (t4.joinable()) {
		t4.join();
		std::cout << "\nt4 joined\n";
	}
	if (t5.joinable()) {
		t5.join();
		std::cout << "\nt5 joined\n";
		end = std::chrono::system_clock::now();
	}
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "computation runs for " << elapsed.count() << " seconds\n";
	
	return 0;
}