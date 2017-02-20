#include<random>
#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>
#include<chrono>
//print vector
void print(std::vector<int>& v) {
	for (auto i : v)
		std::cout << i << ' ';
	std::cout << '\n';
}

int main() {
	//a)
	std::vector<int> vint;
	int N = 20;
	//create a large vector of ints
	for (int i = 0; i < N; ++i)
		vint.push_back(std::rand() % 30);
	print(vint);
	int seed = 1, mul = 7, mod = 19, incre = 1;
	//shuffle vint with user-defined generator
	std::random_shuffle(vint.begin(), vint.end(), [&](int i) {
		for (int j = 0; j < i; ++j)
			seed = (seed*mul + incre) % mod;
		return seed;
	});
	//print out vector after random shuffle
	std::cout << "after random shuffle with user-defined generator\n";
	print(vint);

	//after random_shuffle
	std::random_shuffle(vint.begin(), vint.end());
	std::cout << "after random shuffle with default setting\n";
	print(vint);

	//b)

	//implement with mt19937
	std::cout << "after shuffle with mt19937\n";
	std::mt19937 e2;
	std::shuffle(vint.begin(), vint.end(), e2);
	print(vint);
	
	//implement with default_random_engine
	std::cout << "after shuffle with default random engine\n";
	std::default_random_engine e3;
	std::shuffle(vint.begin(), vint.end(), e3);
	print(vint);

	//implement with linear_congruential_engine
	std::cout << "after shuffle with linear congruential engine\n";
	std::linear_congruential_engine<unsigned int,7,1,9979> e4;
	std::shuffle(vint.begin(), vint.end(), e4);
	print(vint);

	return 0;

}