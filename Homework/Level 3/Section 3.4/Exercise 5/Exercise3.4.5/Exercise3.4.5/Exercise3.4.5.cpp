#include<iostream>
#include<array>
#include<numeric>
#include<chrono>
#include<future>
#include<thread>
#include<omp.h>
#include<vector>
//size of array
const std::size_t N = 10'000;

//b)
double sumup(std::vector<double> v) {
	if (v.size() <= 1000) {
		return std::accumulate(v.begin(), v.end(), 0.0, std::plus<long double>());
	}
	else {
		int mid = v.size() / 2;
		//create the right part vector
		std::vector<double> vRight(v.begin() + mid, v.end());
		//create the left part vector
		std::vector<double> vLeft(v.begin(), v.begin() + mid);
		std::shared_future<double> sumRight(std::async(sumup, vRight));
		//call sum recursively
		return sumup(vLeft) + sumRight.get();
	}
}

//f)
double multi(double x, double y) { return x*y; }


int main() {
	double ini = 0;
	//a)create a large numeric array
	std::cout << "For a)\n";
    std::array<double, N> arr;
	double val = 1;
	for (int i = 0; i < N; ++i)
		arr[i] = val;
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	double sum = std::accumulate(arr.begin(), arr.end(), ini);
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	//get duration
	std::chrono::duration<double> d=end - start;
	//print out
	std::cout << "It takes " << d.count() << " seconds to get the result " << sum << std::endl;

	//b)
	std::cout << "\nFor b):\n";
	//c) measure processing time
	start = std::chrono::system_clock::now();
	//right part index ranges from N/2 to N
	std::vector<double> v1(arr.begin(), arr.end());
	double bSum = sumup(v1);
	end = std::chrono::system_clock::now();
	//measure the time
	std::chrono::duration<double> bd = end - start;
	//print out result and speedup time
	std::cout << "It takes " << bd.count() << " seconds to get the result " << bSum << std::endl;
	std::cout << "b is quicker than a by " << d.count() - bd.count() << " seconds\n";

	//d) compare with performance of OpenMP
	std::cout << "\nFor d)\n";
	omp_set_num_threads(2);
	double sumParallel = 0;
	start = std::chrono::system_clock::now();
#pragma omp parallel for reduction(+:sumParallel)
	for (long i = 0; i < arr.size(); ++i)
		sumParallel += arr[i];
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> openD = end - start;
	//print out result
	std::cout << "It takes " << openD.count() << " seconds to get the result " << sumParallel << std::endl;
	//compare speed with algorithm in b)
	std::cout << "OpenMap is quicker than b) by " << bd.count() - openD.count() << std::endl;
	
	//e)Use threads to accumulate
	std::cout << "\nFor e)\n";
	double eSumL = 0;
	double eSumR = 0;
	start = std::chrono::system_clock::now();
	//sum left half
	std::thread tLeft([&]() {eSumL = std::accumulate(arr.begin(), arr.begin() + N / 2, 0); });
	//sum right half
	std::thread tRight([&]() {eSumR = std::accumulate(arr.begin() + N / 2, arr.begin() + N, 0); });
	tLeft.join();
	tRight.join();
	double eSum = eSumL + eSumR;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> eDuration = end - start;
	//print out result
	std::cout << "It takes " << eDuration.count() << " seconds to get the sum " << eSum << std::endl;
	std::cout << "e method is quicker than algorithm in b) by " << bd.count() - eDuration.count() << std::endl;

	//f)
	//parallel code to compute product of all elements
	double product = 0;
	std::thread t([&]() {product = std::accumulate(arr.begin(), arr.end(), 1, multi); });
	t.join();
	std::cout << "Product of arr elements is " << product << std::endl;

	return 0;
		
}