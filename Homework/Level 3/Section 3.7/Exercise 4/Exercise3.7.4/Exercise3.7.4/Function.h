#ifndef Function_H
#define Function_H
#include<vector>
#include<tuple>
#include<algorithm>
#include<numeric>
#include<iostream>
#include<functional>

using Vector = std::vector<int>;
using Vtuple = std::vector<std::tuple<int, int>>;

//a)count frequency
Vtuple count_f(const Vector& v) {
	Vtuple result;
	Vector vcopy(v);
	//sort vcopy
	std::sort(vcopy.begin(), vcopy.end());
	//get unique elements of v
	auto iter = std::unique(vcopy.begin(), vcopy.end());
	//v.resize(std::distance(v.begin(), iter));
	for (auto it = vcopy.begin(); it != iter; ++it) {
		//get frequency for each element of v
		int count = std::count(v.begin(), v.end(), *it);
		//push to result
		result.push_back(std::make_tuple(*it, count));
	}
	return result;
}
//b)
using Tuple4 = std::tuple<double, double, double, double>;
Tuple4 stat(const std::vector<double>& v) {
	//get sum
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	//get average
	double average = sum / v.size();
	//get pair of iterators of minmax
	auto minmax = std::minmax_element(v.begin(), v.end());
	double min = *minmax.first;
	double max = *minmax.second;
	//return result
	return std::make_tuple(min, max, sum, average);
}

#endif

