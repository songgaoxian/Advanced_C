#include<iostream>
#include<thread>
#include<string>
#include<functional>
#include<chrono>
#include<vector>
#include<mutex>

std::mutex p_mutex;

//copy code from 3.1.1
void Iprint(const std::string& s, int count) {
	p_mutex.lock(); //control shared resource
	std::cout << "print " << count << " times\n";
	for (int i = 0; i < count; ++i)
		std::cout << s << std::endl;
	//get deadlock, which will result in infinite loop if comment the following line
	p_mutex.unlock(); //the resource can be used for another thread
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
	//copy codes from exercise 3.1.1
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
	std::function<void(const std::string&, int)> f4 = std::bind(&print4::display2, p4, std::placeholders::_1, std::placeholders::_2);
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
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "computation runs for " << elapsed.count() << " seconds\n";
	//a)it takes 1.17067 seconds to finish computation
	//b)it takes 1.15582 seconds to finish computation
	return 0;
}