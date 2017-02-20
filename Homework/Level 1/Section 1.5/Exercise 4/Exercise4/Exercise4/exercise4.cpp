#include "adapter.h"
#include<iostream>
int main() {
	std::vector<double> v1 = { 3.2,4.5,7.8,0.1,8.9 };
	AdaptorIndex<double> adp(std::move(v1));
	std::cout << adp(3.5)<<std::endl;
	std::vector<double> v2 = { 1.1,5.5,2.4,9.9,5.6 };
	std::vector<double> v3 = { 5.5,3.3,2.2,1.1,0.9 };
	AdapterErr<double> adpe(std::move(v2), std::move(v3));
	std::tuple<std::size_t, double, std::size_t, double> summary = adpe(1,4);
	std::size_t maxAbsIndex, maxRelIndex;
	double absErr, relErr;
	std::tie(maxAbsIndex, absErr, maxRelIndex, relErr) = summary;
	std::cout << "max absolute index and error: " << maxAbsIndex << ", " << absErr << std::endl;
	std::cout << "max relative index and error: " << maxRelIndex << ", " << relErr << std::endl;
	return 0;

}