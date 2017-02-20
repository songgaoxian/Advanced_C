#include<iostream>
#include<thread>
#include<string>
#include<functional>
#include<chrono>
#include<vector>

//print string s count times
void Iprint(const std::string& s, int count) {
	std::cout << "print " << count << " times\n";
	for (int i = 0; i < count; ++i)
		std::cout << s << std::endl;
}
//a)
//free function
void print1(const std::string& s, int count) {
	std::cout << "\nIn print1: ";
	std::cout << std::this_thread::get_id() << std::endl;
	Iprint(s, count);
}
//lambda function
auto print2 = [](const std::string& s, int count) {
	std::cout << "\nIn print2: ";
	std::cout << std::this_thread::get_id() << std::endl;
	Iprint(s, count);
};
//function object
struct print3 {
	print3() {}
	void operator()(const std::string& s, int count) {
		std::cout << "\nIn print3: ";
		std::cout << std::this_thread::get_id() << std::endl;
		Iprint(s, count);
	}
};
class print4 {
public:
	print4() {}
	//static member function
	static void display(const std::string& s, int count) {
		std::cout << "\nIn print4 static member: ";
		std::cout << std::this_thread::get_id() << std::endl;
		Iprint(s, count);
	}
	void display2(const std::string& s, int count) {
		std::cout << "\nIn print4 member: ";
		std::cout << std::this_thread::get_id() << std::endl;
		Iprint(s, count);
	}
};
//end of a)

int main() {
	//f)
	//create start and end time points
	std::chrono::time_point<std::chrono::system_clock> start, end;
	//reccord the starting time point
	start = std::chrono::system_clock::now();

	//b)
	//specify parameters for each function
	
		std::string s("glad to know not alone");
		int count = 5;

		//t1 is a detached thread for global function
		std::thread t1(&print1, std::ref(s), count);
		t1.detach();
		//print t1 thread id e)
		std::cout << "\nt1 thread id: " << t1.get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));

		//t2 is created for lambda function
		std::thread t2([](const std::string& s, int count) {std::cout << "\nIn lambda: ";  Iprint(s, count); }, std::ref(s), count);
		//print t2 thread id e)
		std::cout << "\nt2 thread id: " << t2.get_id() << std::endl;
		
		//tt2 is created with stored lambda
		std::thread tt2(print2, std::ref(s), count);
		//print tt2 thread id e)
		std::cout << "\ntt2 thread id: " << tt2.get_id() << std::endl;

		//t3 is created with function object
		print3 p3;
		std::thread t3(&print3::operator(), p3, std::ref(s), count);
		//print t3 thread id e)
		std::cout << "\nt3 thread id: " << t3.get_id() << std::endl;

		//t4 is created with static member
		std::thread t4(&print4::display, std::ref(s), count);
		//print t4 thread id e)
		std::cout << "\nt4 thread id: " << t4.get_id() << std::endl;

		print4 p4;
		//t5 is created with binded member function
		std::function<void(const std::string&,int)> f4 = std::bind(&print4::display2, p4, std::placeholders::_1,std::placeholders::_2);
		std::thread t5(f4, std::ref(s),count);
		//print t5 thread id e)
		std::cout << "\nt5 thread id: " << t5.get_id() << std::endl;
		//end of b)

		//c	
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
		/*if (t5.joinable()) {
			t5.join(); //finished executing
			std::cout << "\nt5  joined\n";
		}*/

		//end of c)

		//d)
		//use exception handling to join t5 which is not joined
		try {
			//t5 is not joined, then throw an exception
			if (t5.joinable()) {
				throw std::string("\nt5 is not joined\n");
			}
		}
		catch (...) {
				t5.join();
				std::cout << "\nt5 joined\n";
		}
		//end of d)
		
		//f) record finished time point
		end = std::chrono::system_clock::now();
		//get the duration of running time
		std::chrono::duration<double> elapsed = end - start;
		//print out running time
		std::cout << "computation runs for " << elapsed.count() << " seconds\n";
		//end of f)
		//finding:Implementations of Iprint are not executed sequentially in all the created threads
		return 0;
}