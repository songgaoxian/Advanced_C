#include<iostream>
#include<forward_list>
#include<iterator>

//b)
template<typename T>
int GetSize(std::forward_list<T>& flist) {
	auto first = flist.begin();
	auto last = flist.end();
	return std::distance(first, last);
}

int main() {
	//a)create forward lists
	std::forward_list<int> defaultList;
	std::size_t N = 4;
	double val = 2.2;
	std::forward_list<double> anotherList(N, val);
	std::forward_list<double> initialiserList{ 1.1,2.2,3.3,4.4 };
	std::forward_list<double> anotherList2(anotherList);
	//b)
	std::cout << "Check size of anotherList\n";
	std::cout << GetSize(anotherList) << std::endl;
	//c)
	//original list
	std::cout << "original list:\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++) {
		std::cout << *iter << " ";
	}
	//insert after a position based on value
	std::forward_list<double>::iterator it = initialiserList.begin();
	it++;
	it = initialiserList.insert_after(it, val);
	std::cout << "\nafter first insertion\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";
	//insert after a position based on value and count
	int count = 2;
	val = 5.9;
	it = initialiserList.insert_after(it, count, val);
	std::cout << "\nafter second insertion\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";
	//insert based on two iterators
	it = initialiserList.insert_after(it, anotherList.begin(), anotherList.end());
	std::cout << "\nafter third insertion\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";
	//insert based on initialiser list
	it = initialiserList.insert_after(it, { 1,2.9,3 });
	std::cout << "\nafter fourth insertion\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";
   
	//d)
	auto it2 = initialiserList.begin();
	it2++;
	it2++;
	it2++;
	//erase after a position
	it2 = initialiserList.erase_after(it2);
	std::cout << "\nafter first erasing\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";
	//erase after two iterators
	it2 = initialiserList.erase_after(it2, initialiserList.end());
	std::cout << "\nafter second erasing\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";

	//e)merge
	initialiserList.sort();
	anotherList.sort();
	initialiserList.merge(anotherList);
	std::cout << "\nafter merge initialiserList and anotherList\n";
	for (auto iter = initialiserList.begin(); iter != initialiserList.end(); iter++)
		std::cout << *iter << " ";
	//e)splice
	std::cout << "\nOriginal anotherList2\n";
	for (auto iter = anotherList2.begin(); iter != anotherList2.end(); iter++)
		std::cout << *iter << " ";
	it2 = initialiserList.begin();
	it2++;
	it2++;
	it2++;
	//transfer elements after initialiserList2.begin() and before it2 to anotherList2
	anotherList2.splice_after(anotherList2.before_begin(), initialiserList, initialiserList.begin(), it2); 
	std::cout << "\nAfter splice anotherList2\n";
	for (auto iter = anotherList2.begin(); iter != anotherList2.end(); iter++)
		std::cout << *iter << " ";


	return 0;
}