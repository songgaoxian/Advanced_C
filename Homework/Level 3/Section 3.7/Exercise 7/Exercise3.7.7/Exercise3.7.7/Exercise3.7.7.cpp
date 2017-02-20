#include<vector>
#include<algorithm>
#include<iostream>

//c)compute power set of S
using VectorV = std::vector<std::vector<int>>;
VectorV PowerSet(std::vector<int>& s) {
	//store all subsets
	VectorV result;
	//store one subset
	std::vector<int> existSet;
	//store empty subset
	result.push_back(existSet);
	int count, mark;
	for (int i = 0; i < s.size(); ++i) {
		count = 0;
		mark = result.size();
		//construct new subsets by pushing s[i] into every existing subset
		while (count < mark) {
			//get existing set
			existSet = result[count];
			//push s[i] into every existing set
			existSet.push_back(s[i]);
			//push modified existing set to result
			result.push_back(existSet);
			count++;
		}

	}

	return result;
}


int main() {
	std::vector<int> S{ 1,-1,7,8,9,10 };
	//a)
	//copy to this vector
	std::vector<int> scopy(S.size());
	//reverse and copy
	std::reverse_copy(S.begin(), S.end(), scopy.begin());
	//print out
	std::cout << "after reverse copy\n";
	std::for_each(scopy.begin(), scopy.end(), [](int x) {std::cout << x << ' '; });
	std::cout << '\n';

	//b)
	//rotate S so value 8 is the begining
	std::rotate(S.begin(), S.begin() + 3, S.begin() + 4);
	//print out
	std::cout << "after rotate\n";
	std::for_each(S.begin(), S.end(), [](int x) {std::cout << x << ' '; });
	std::cout << '\n';

	//c)
	//get power set
	VectorV pset = PowerSet(S);
	std::cout << "There are " << pset.size() << " subsets\n";
	std::cout << "display subsets: \n";
	for (int i = 0; i < pset.size(); ++i) {
		for (int j = 0; j < pset[i].size(); ++j)
			std::cout << pset[i][j] << " ";
		std::cout << '\n';
	}

	//d)move subset 8 9 10 to the front
	//get the original S
	std::rotate(S.begin(), S.begin() + 1, S.begin() + 4);
	//move 8,9,10 to front
	std::rotate(S.begin(), S.begin() + 3, S.end());
	std::cout << "after rotate\n";
	std::for_each(S.begin(), S.end(), [](int x) {std::cout << x << ' '; });
	std::cout << '\n';

	return 0;
}