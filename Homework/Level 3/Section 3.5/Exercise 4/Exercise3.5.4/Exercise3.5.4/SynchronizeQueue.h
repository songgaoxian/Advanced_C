#ifndef SynchronizeQ_H
#define SynchronizeQ_H
#include<iostream>
#include<queue>
#include<thread>
#include<mutex>

template<typename T, typename Container, typename Comparator>
class SyncQueue {
private:
	std::priority_queue<T, Container, Comparator>* pQ;
	std::mutex m;
	std::condition_variable m_cond;
public:
	//default constructor
	SyncQueue() {}
	//another constructor
	SyncQueue(std::priority_queue<T, Container, Comparator>* srcPQ) :pQ(srcPQ) {}
	//enque
	void Enque(T element) {
		//locking mechanism
		std::unique_lock<std::mutex> lock(m);
		//enque operation
		(*pQ).push(element);
		//notify that data is read
		m_cond.notify_one();
	}//lock released
	 //dequeue
	T Dequeue() {
		//locking mechanism
		std::unique_lock<std::mutex> lock(m);
		//wait for data to be ready
		while ((*pQ).size() == 0) m_cond.wait(lock);
		//dequeue operation
		T result = (*pQ).top(); (*pQ).pop();
		return result;
	}
};

#endif
