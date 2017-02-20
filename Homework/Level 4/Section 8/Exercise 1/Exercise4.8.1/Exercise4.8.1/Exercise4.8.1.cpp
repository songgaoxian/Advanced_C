//Exercise4.8.1
//
//apply heap syntax
//written on 2016/6/22

#include<algorithm>
#include<iostream>
#include<vector>

void printHeap(const std::vector<int>& vec2) {
	//initialise max
	int max = 1;
	auto it = vec2.begin();
	//initialise count
	int count = 0;

	//print out the heap
	while (it != vec2.end()) {
		//print out one element
		std::cout << *it << ",";
		//count number of elements already existed in the row
		count++;
		//max is the maximum number of elements allowed in the row
		if (count == max) {
			//if count==max, print new line
			std::cout << '\n';
			//reset count and max for next row
			count = 0;
			max *= 2;
		}
		//increment iterator
		it++;
	}
	std::cout << '\n';
}

int main() {
	//a)create a vector
	std::vector<int> vec2{ 3,4,5,6,7,5,6,7,8,9,1,2,3,4 };
	std::vector<int> vectorCopy(vec2);

	//b)call make_heap()
	std::make_heap(vec2.begin(), vec2.end());
	std::cout << "b)\n";
	printHeap(vec2);
	//The heap is like this
	/*               9
	          8                 6
	      7      7          5      5
		3  6    4  1      2  3    4
	*/

	//c)call pop_heap
	std::pop_heap(vec2.begin(), vec2.end());
	std::cout << "\nc)\n";
	printHeap(vec2);
	//after calling pop_heap, the root is moved to the last position in the heap
	//so we need to call pop_back to remove it from the heap
	vec2.pop_back();
	std::cout << "\nAfter calling pop_back:\n";
	printHeap(vec2);
	
	//test pop_heap for non-heap vector
	//std::pop_heap(vectorCopy.begin(), vectorCopy.end());//result in run-time error

	//d)
	std::cout << "\nd)\n";
	//call push_back first, because we need to add element to the heap;
	//push_heap will then move the element added to propoer position in the heap
	vec2.push_back(6);
	std::push_heap(vec2.begin(), vec2.end());
	printHeap(vec2);

	//std::push_heap(vectorCopy.begin(), vectorCopy.end());//result in run-time error

	//e)sort heap
	std::sort_heap(vec2.begin(), vec2.end());
	std::cout << "\ne)\nAfter sorting the heap:\n";
	printHeap(vec2);

	//f)
	//make vectorCopy be a max heap
	std::make_heap(vectorCopy.begin(), vectorCopy.end(), std::less<int>());
	std::cout << "\nf)\n";
	//the largest element is the root
	std::cout << "Largest element in heap vectorCopy: " << vectorCopy.front() << '\n';

	return 0;
}