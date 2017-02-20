#include "Queue.h"

int main() {
	//declare queue
	std::queue<int> q1;
	q1.push(1); q1.push(2); q1.push(3);
	//create object of sQueue
	sQueue<int> sQ(q1);
	sQueue<int>* pSQ=&sQ;
	int code = 3;
	//create producer and consumer
	Producer p(code, pSQ);
	Consumer c(pSQ);
	//create threads for p and c
	boost::thread t1(&Producer::produce, p);
	boost::thread t2(&Consumer::consume, c);
	getchar(); //you can decide how long to terminate
	
	//interrupt t1 and t2 to terminate threads
	t1.interrupt();
	t2.interrupt();
	t1.join();
	t2.join();
	return 0;
}