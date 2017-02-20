#include<vector>
#include<iostream>
#include<algorithm>
#include<set>
#include<functional>
#include<chrono>
//use predefined STL function object
std::set<int> transformToSet1(std::vector<int>& v, int thresh) {
	//copy qualified values to set s
	auto it=std::remove_if(v.begin(), v.end(), std::bind2nd(std::less_equal<int>(), thresh));
	return std::set<int>(v.begin(), it);
}

//use user-defined function object
struct LessEqual {
	int val;
	LessEqual(int src) :val(src) {}
	bool operator()(int x) { return x <= val; }
};
//apply LessEqual in tranform
std::set<int> transformToSet2(std::vector<int>&v, int thresh) {
	LessEqual lessEqual(thresh);
	//copy qualified values to set s
	auto it=std::remove_if(v.begin(), v.end(), lessEqual);
	return std::set<int>(v.begin(), it);
}

//use lambda function
std::set<int> transformToSet3(std::vector<int>& v, int thresh) {
	//copy qualified values to set s
	auto it=std::remove_if(v.begin(), v.end(), [=](int x) {return x <= thresh; });
	return std::set<int>(v.begin(), it);
}


int main() {
	//empty set
	std::set<int> s1,s2,s3;
	//operate on vectors
	std::vector<int> v1;
	int N = 3000;
	for (int i = 0; i < N; ++i) {
		v1.push_back(rand() % 5);
	}
	std::vector<int> v2(v1);
	std::vector<int> v3(v1);
	//set threshhold value
	int thresh = 2;
	//call functions to transform and get duration of each process
	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<double> d1, d2, d3;
	
	//record start time of transformToSet1
	start = std::chrono::system_clock::now();
	s1=transformToSet1(v1, thresh);
	//record end time
	end = std::chrono::system_clock::now();
	//get duration
	d1 = end - start;
	
	//record start time of transformToSet1
	start = std::chrono::system_clock::now();
	s2=transformToSet2(v2, thresh);
	//record end time
	end = std::chrono::system_clock::now();
	//get duration
	d2 = end - start;

	//record start time of transformToSet1
	start = std::chrono::system_clock::now();
	s3=transformToSet3(v3, thresh);
	//record end time
	end = std::chrono::system_clock::now();
	//get duration
	d3 = end - start;

	//print out set value
	std::cout << "print out sets' values\n";
	for (auto it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << " ";
	std::cout << '\n';
	for (auto it = s2.begin(); it != s2.end(); ++it)
		std::cout << *it << " ";
	std::cout << '\n';
	for (auto it = s3.begin(); it != s3.end(); ++it)
		std::cout << *it << " ";
	std::cout << '\n';

	//print out duration
	std::cout << "With predefined STL object, it takes " << d1.count() << " seconds to get the result\n";
	std::cout << "With user-defined function object, it takes " << d2.count() << " seconds to get the result\n";
	std::cout << "With lambda function, it takes " << d3.count() << " seconds to get the result\n";

	//understandablity: based on this example, lambda function and function object implemented methods are more understandable;
	//maintainablity: function object and lambda function can be customized and adapted easily for changing requirements
	//efficiency, the running time for the three methods are approximately same; 
	return 0;
}