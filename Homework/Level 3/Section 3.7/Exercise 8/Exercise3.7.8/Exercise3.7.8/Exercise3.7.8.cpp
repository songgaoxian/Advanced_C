#include<stack>
#include<algorithm>
#include<iostream>
#include<random>
//Remove
template<typename T>
void max(std::stack<T>& stk) {
	//the top val is ready for comparison
	T val1 = stk.top();
	stk.pop();
	//the second top val is ready for comparison
	T val2 = stk.top();
	stk.pop();
	//leave the larger value on stack
	if (val1 > val2)
		stk.push(val1);
	else
		stk.push(val2);
}
//Remove
template<typename T>
void min(std::stack<T>& stk) {
	//the top val is ready for comparison
	T val1 = stk.top();
	stk.pop();
	//the second top val is ready for comparison
	T val2 = stk.top();
	stk.pop();
	if (val1 > val2)
		stk.push(val2);
	else
		stk.push(val1);
}
//Modify
template<typename T>
void over(std::stack<T>& stk) {
	stk.pop();
	//get second top val
	T val = stk.top();
	//duplicate val on top
	stk.push(val);
}
//Mutate
template<typename T>
void rot(std::stack<T>& stk) {
	//get top element
	T top1 = stk.top();
	stk.pop();
	//get second top element
	T top2 = stk.top();
	stk.pop();
	//get third top element
	T top3 = stk.top();
	stk.pop();
	//push second top element
	stk.push(top2);
	//push top element
	stk.push(top1);
	//push third top element
	stk.push(top3);
	//rotation finished
}
//Mutate
template<typename T>
void swap(std::stack<T>& stk) {
	//get top val
	T top1 = stk.top();
	stk.pop();
	//get second top val
	T top2 = stk.top();
	stk.pop();
	//push top1 to stk
	stk.push(top1);
	//push top2 to stk
	stk.push(top2);
}
//Remove
template<typename T>
void drop(std::stack<T>& stk) {
	stk.pop();
}
//print
template<typename T>
void print(std::stack<T> stk) {
	while (!stk.empty()) {
		//print out top value
		std::cout << stk.top() << ' ';
		stk.pop();
	}
	std::cout << '\n';
}

int main() {
	//test these operations
	std::stack<int> stk;
	int N = 10;
	for (int i = 0; i < N; ++i)
		stk.push(std::rand() % 30);
	
	std::cout << "original stack:\n";
	print<int>(stk);

	max<int>(stk);
	std::cout << "after max:\n";
	print<int>(stk);

	min<int>(stk);
	std::cout << "after min:\n";
	print<int>(stk);

	over<int>(stk);
	std::cout << "after over:\n";
	print<int>(stk);

	rot(stk);
	std::cout << "after rot:\n";
	print(stk);

	swap(stk);
	std::cout << "after swap:\n";
	print(stk);

	drop(stk);
	std::cout << "after drop:\n";
	print(stk);

	return 0;
}