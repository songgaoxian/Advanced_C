#include "Command.h"


int main() {
	
	pQue queue;
	SyncQueue sQ(queue);
	//product produced by producer 1
	long typicalPriority1 = 1;
	Command typical1([](double x) {return x * 2; }, typicalPriority1);
	//product produced by producer 2
	long typicalPriority2 = 2;
	Command typical2([](double x) {return x * 3; }, typicalPriority2);
	//product produced by producer 3
	long typicalPriority3 = 3;
	Command typical3([](double x) {return x * 4; }, typicalPriority3);

	//producer and consumer ids
	int pid1 = 1, pid2 = 2, pid3 = 3;
	int cid1 = 1, cid2 = 2, cid3 = 3;
	//create producers
	Producer p1(pid1,&sQ,typical1,20);
	Producer p2(pid2, &sQ,typical2,24);
	Producer p3(pid3, &sQ,typical3,13);
	//create consumers
	Consumer c1(cid1, &sQ,1.2);
	Consumer c2(cid2, &sQ,1.4);
	Consumer c3(cid3, &sQ,1.9);
	//create thread groups
	//boost::thread_group producers;
	//boost::thread_group consumers;
	//port to c++11
	std::vector<std::thread> producers;
	std::vector<std::thread> consumers;
	//create thread groups for producers
	//producers.create_thread(p1);
	//producers.create_thread(p2);
	//producers.create_thread(p3);
	//port to c++11
	producers.push_back(std::thread(p1));
	producers.push_back(std::thread(p2));
	producers.push_back(std::thread(p3));
	//create thread groups for consumers
	//consumers.create_thread(c1);
	//consumers.create_thread(c2);
	//consumers.create_thread(c3);
	//port to c++11
	consumers.push_back(std::thread(c1));
	consumers.push_back(std::thread(c2));
	consumers.push_back(std::thread(c3));
	//join thread groups
	//consumers.join_all();
	//producers.join_all();
	//port to c++11
	for (auto it = producers.begin(); it != producers.end(); it++)
		(*it).join();
	for (auto it = consumers.begin(); it != consumers.end(); it++)
		(*it).join();

	return 0;
}
