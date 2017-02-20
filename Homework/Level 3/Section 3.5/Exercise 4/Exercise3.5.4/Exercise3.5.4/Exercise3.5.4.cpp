#include<vector>
#include<chrono>
#include "SynchronizeQueue.h"
//d) test this class
int main() {
	//construct priority queue
	int arr[] = { 22,33,11,99 };
	std::priority_queue<int, std::vector<int>, std::greater<int>> priorityQ(arr,arr+4);
	SyncQueue<int, std::vector<int>, std::greater<int>> sQ(&priorityQ);
	//deque atmost 5 times
	int maxDequeTime = 5;
	//enque atmost 10 times
	int maxEnqueTime = 10;
	//deque thread
	std::thread tDeque([&]() {
		while (maxDequeTime > 0) {
			std::cout << sQ.Dequeue() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			maxDequeTime--;
		}
	});
	//enque thread
	int val = 55;
	std::thread tEnque([&]() {
		while (maxEnqueTime > 0) {
			sQ.Enque(val);
			std::cout << "\nEnqued " << val << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			val++;
			maxEnqueTime--;
		}
	});
	tDeque.join();
	tEnque.join();
	return 0;
}