#ifndef Queue_H
#define Queue_H
#include<queue>
#include<boost/thread.hpp>
#include<boost/thread/mutex.hpp>
#include<boost/chrono.hpp>
#include<iostream>
#include<chrono>

template<typename T>
class sQueue {
private:
	std::queue<T> m_queue;
	boost::mutex m_mutex;
	boost::condition_variable m_cond;
public:
	sQueue(const std::queue<T>& q){
		m_queue = q;
	}
	void queuing(const T& input) {
		boost::unique_lock<boost::mutex> lck(m_mutex);
		m_queue.push(input); //enque input
		m_cond.notify_one(); //wake up one waiting thread
	}
	T& deque() {
		boost::unique_lock<boost::mutex> lck(m_mutex);
		while (m_queue.size() == 0) {
			m_cond.wait(lck);
		}
		T& result = m_queue.front();
		m_queue.pop();
		return result;
	}
};

class Producer {
private:
	int m_productCode;
	sQueue<int>* m_queue;
public:
	//give a constructor
	Producer(int code, sQueue<int>* queue) : m_productCode(code),m_queue(queue) {}
	//produce product at 1 second per product
	void produce() {
		int code = m_productCode;
		while (true) {
			m_queue->queuing(++code);
			std::cout << "produce " << code << "; ";
			boost::this_thread::sleep_for(boost::chrono::seconds(1));
		}
	}
};

class Consumer {
private:
	sQueue<int>* m_queue;
public:
	Consumer(sQueue<int>* queue) : m_queue(queue) {}
	//consume product at 1 second per product
	void consume() {
		while (true) {
			std::cout << "consume " << m_queue->deque() << "; ";
			boost::this_thread::sleep_for(boost::chrono::seconds(1));
		}
	}

};
#endif
