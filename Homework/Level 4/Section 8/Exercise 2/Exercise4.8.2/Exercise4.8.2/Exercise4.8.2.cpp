//Exercise4.8.2
//
//use priority queue
//written on 2016/6/22

#include<vector>
#include<iostream>
#include<queue>
#include<functional>
//print copied priority queue
template<typename ContainerQ>
void print(ContainerQ pQ) {
	while (!pQ.empty()) {
		//print top element of pQ
		std::cout << pQ.top() << ',';
		//pop the top element
		pQ.pop();
	}
	std::cout << '\n';
}

int main() {
	//a)create default priority queue
	std::cout << "a)\n";
	std::vector<int> v{ 10,5,20,30,25,7,40 };
	std::priority_queue<int> pQ(v.begin(), v.end());
	print(pQ);

	//b)use std::greater<int>
	std::priority_queue<int, std::vector<int>, std::greater<int>> pQ2(v.begin(), v.end());
	std::cout << "\nb)\n";
	print(pQ2);

	//c)
	//comparator
	auto cmp = [](int left, int right)->bool {return (left > right); };
	//create priority_queue with comparator cmp
	std::priority_queue<int, std::vector<int>,decltype(cmp)> pQ3(v.begin(), v.end(),cmp);
	std::cout << "\nc)\n";
	print(pQ3);

	return 0;
}