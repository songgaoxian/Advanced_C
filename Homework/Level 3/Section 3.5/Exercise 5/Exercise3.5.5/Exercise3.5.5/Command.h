#ifndef Command_H
#define Command_H
#include<functional>
#include<boost/thread.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<iostream>
#include<queue>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>


//copied
using FunctionType = std::function<double(double)>;
class Command {
private:  
	long ID; // priority of command  
	FunctionType algo;  

public: 
	Command(const FunctionType& algorithm, long priority) : algo(algorithm), ID(priority) {}
	Command() {}	
	void Execute(double x) {   
			// Introduce delay to simulate a heavy algorithm   
			boost::this_thread::sleep (boost::posix_time::millisec(5000));   
			std::cout << algo(x) << '\n';  }  
	long priority() const { return ID; }
};
//copied from exercise 2
struct Comparator {
	Comparator() {}
	bool operator()(const Command& c1, const Command& c2) {
		return c1.priority() < c2.priority();
	}
};

using pQue = std::priority_queue<Command, std::vector<Command>, Comparator>;

//create synchronize queue
class SyncQueue {
private:
	pQue m_queue;
	//for synchronization and notify
	//boost::mutex m_mutex;
	//port to c++11
	std::mutex m_mutex;
	//boost::condition_variable m_cond;
	//port to c++11
	std::condition_variable m_cond;
public:
	SyncQueue(pQue src):m_queue(src){}
	//enque of synchronized queue
	void Enque(Command c) {
		//boost::unique_lock<boost::mutex> lock(m_mutex);
		//port to c++11;
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(c);
		m_cond.notify_one();
	}
	//deque operation
	Command Deque() {
		//boost::unique_lock<boost::mutex> lock(m_mutex);
		//port to c++11
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_queue.empty()) m_cond.wait(lock);
		//not empty
		Command result = m_queue.top();
		m_queue.pop();
		return result;
	}
};

//create producer
class Producer {
private:
	int m_id;
	SyncQueue* m_queue;
	Command m_Product;
	int maxProduction;
public:
	//constructor
	Producer(int id, SyncQueue* queue,Command product, int max) :m_id(id), m_queue(queue),m_Product(product),maxProduction(max) {}
	//default constructor
	Producer() {}
	//produce operation
	void operator()() {
		std::cout << "start producing\n";
		int count = 0;
		while (count <= maxProduction) {
			//produce one typical command
			std::cout << "Produce one with priority " << m_Product.priority() << std::endl;
			m_queue->Enque(m_Product);
			count++;
			if (count == maxProduction) {
				//this is the termination signal
				m_queue->Enque(Command([](double x) {return x; }, -1));
				std::cout << "Producing ends\n";
			}
			//boost::this_thread::sleep(boost::posix_time::millisec(50));
			//port to c++11
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}		
	}
};
class Consumer {
private:
	int m_id;
	SyncQueue* m_queue;
	double x;
public:
	//constructor
	Consumer() {}
	Consumer(int id, SyncQueue* queue,double src) :m_id(id), m_queue(queue),x(src) {}
	//consume operation
	void operator() () {
		std::cout << "start consuming\n";
		Command result;
		do {
			result = m_queue->Deque();
			result.Execute(x);
			std::cout << "consume one with priority " << result.priority() << std::endl;
			//boost::this_thread::sleep(boost::posix_time::millisec(50));
			//port to c++11
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		} while (result.priority() > 0);//if the consumed object is termination signal, consume stops
	}
};

#endif