#include<queue>
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>

int main() {
	//a)create a priority queue
	std::priority_queue<long long,std::vector<long long>,std::less<long long>> pQueue;
	pQueue.push(66);
	pQueue.push(22);
	pQueue.push(44);
	//print top element and popo it
	std::cout << "Top element is " << pQueue.top() << std::endl;
	pQueue.pop();
	pQueue.push(11);
	pQueue.push(22);
	pQueue.push(33);
	pQueue.pop();
	while (!pQueue.empty()) {
		std::cout << "Element to pop out: " << pQueue.top() << std::endl;
		pQueue.pop();
	}

	//b)create another priority queue
	std::cout << "\nfor b)\n";
	std::priority_queue<long long, std::deque<long long>, std::greater<long long>> pQueue2;
	pQueue2.push(66);
	pQueue2.push(22);
	pQueue2.push(44);
	//print top element and popo it
	std::cout << "Top element is " << pQueue2.top() << std::endl;
	pQueue2.pop();
	pQueue2.push(11);
	pQueue2.push(22);
	pQueue2.push(33);
	pQueue2.pop();
	while (!pQueue2.empty()) {
		std::cout << "Element to pop out: " << pQueue2.top() << std::endl;
		pQueue2.pop();
	}

	//c)create another priority queue with lambda function: result should be same with b)
	std::cout << "\nfor c)\n";
	auto greaterThan = [](long long& x1, long long& x2) {return x1 > x2;};
	std::priority_queue<long long, std::deque<long long>, decltype(greaterThan)> pQueue3(greaterThan);
	pQueue3.push(66);
	pQueue3.push(22);
	pQueue3.push(44);
	//print top element and popo it
	std::cout << "Top element is " << pQueue3.top() << std::endl;
	pQueue3.pop();
	pQueue3.push(11);
	pQueue3.push(22);
	pQueue3.push(33);
	pQueue3.pop();
	while (!pQueue3.empty()) {
		std::cout << "Element to pop out: " << pQueue3.top() << std::endl;
		pQueue3.pop();
	}
	return 0;
}