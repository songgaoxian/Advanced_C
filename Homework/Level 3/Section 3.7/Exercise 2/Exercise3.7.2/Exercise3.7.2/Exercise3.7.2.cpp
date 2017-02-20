#include<vector>
#include<algorithm>
#include<iostream>
#include<chrono>
#include<random>
#include<functional>
using Vector = std::vector<double>;
//different predicates
bool Comp(double x, double y) { return x < y; }
auto Comp2 = [](double x, double y) {return x < y; };
struct Comp3 {
	Comp3(){}
	bool operator()(double x, double y) { return x < y; }
};


int main() {
	Vector v;
	int N = 3999;
	std::default_random_engine g;
	std::uniform_real_distribution<double> distribution(-100, 100);
	//randomly generate numbers to push to vector v
	for (int i = 0; i < N; ++i) {
		v.push_back(distribution(g));
	}
	//1
	//check efficiency of is_sorted_until with default predicate
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	auto pos = std::is_sorted_until(v.begin(), v.end());
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::cout << "For is_sorted_until with default predicate:\n";
	std::chrono::duration<double> D = end - start;
	std::cout << "It takes " << D.count() << " seconds to get bad value " << *pos << std::endl;
	
	//check efficiency of is_sorted_until with free function
	start = std::chrono::system_clock::now();
	pos = std::is_sorted_until(v.begin(),v.end(),Comp);
	end = std::chrono::system_clock::now();
	std::cout << "For is_sorted_until with free function:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to get bad value " << *pos << std::endl << std::endl;
	//2
	//check efficiency of is_sorted
	start = std::chrono::system_clock::now();
	bool result = std::is_sorted(v.begin(), v.end());
	end = std::chrono::system_clock::now();
	std::cout << "For is_sorted with default predicate:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to get " <<std::boolalpha<<result<< std::endl;

	//check efficiency of is_sorted with lambda function
	start = std::chrono::system_clock::now();
	result = std::is_sorted(v.begin(), v.end(),Comp2);
	end = std::chrono::system_clock::now();
	std::cout << "For is_sorted with lambda function:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to get " << std::boolalpha << result << std::endl<<std::endl;
	//3
	//check efficiency of sort
	Vector v1 = v;
	start = std::chrono::system_clock::now();
	std::sort(v.begin(),v.end());
	end = std::chrono::system_clock::now();
	std::cout << "For sort with default predicate:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to sort vector." << std::endl;

	//check efficiency of sort with function object
	v = v1;
	start = std::chrono::system_clock::now();
	std::sort(v1.begin(), v1.end(),Comp3());
	end = std::chrono::system_clock::now();
	std::cout << "For sort with function object:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to sort vector." << std::endl<<std::endl;
	//4
	//check efficiency of partial_sort
	start = std::chrono::system_clock::now();
	std::partial_sort(v.begin(), v.end() - 100, v.end());
	end = std::chrono::system_clock::now();
	std::cout << "For partial_sort with default predicate:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to partially sort vector.\n";

	//check efficiency of partial_sort with std::greaterthan
	start = std::chrono::system_clock::now();
	std::partial_sort(v.begin(), v.end() - 100, v.end(),std::greater<double>());
	end = std::chrono::system_clock::now();
	std::cout << "For partial_sort with greater:\n";
	D = end - start;
	std::cout << "It takes " << D.count() << " seconds to partially sort vector.\n";

	return 0;
}