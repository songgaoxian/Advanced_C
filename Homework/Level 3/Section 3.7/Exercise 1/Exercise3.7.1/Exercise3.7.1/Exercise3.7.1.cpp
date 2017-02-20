#include<vector>
#include<tuple>
#include<iostream>
#include<algorithm>

using Range = std::tuple<std::size_t, std::size_t>;
using Result = std::tuple<Range, bool>;
template<typename value_type>
using Vector = std::vector<value_type>;

template<typename value_type>
Result find_sequential_greater(const Vector<value_type>& v, value_type x) {
	for (std::size_t j = 0; j < v.size(); ++j) {
		if (v[j] <= x && v[j + 1] > x) {
			return std::make_tuple(std::make_tuple(j, j + 1), true);
		}
	}
	return std::make_tuple(std::make_tuple(999, 999), false);
}
//a)similar functionality with find_if
template<typename value_type>
Result find_sequential_greater2(const Vector<value_type>& v, value_type x) {
	//get the iterator for the first value that is greater than x
	auto it = std::find_if(v.begin(), v.end(), [=](value_type val) {return val > x; });
	//check if successful
	if (it != v.end()) {
		int j = std::distance(v.begin(), it) - 1;
		return std::make_tuple(std::make_tuple(j, j + 1), true);
	}
	return std::make_tuple(std::make_tuple(999, 999), false);	
}
//wrapper for std::find
template<typename value_type>
int find_index(const Vector<value_type>& v, value_type x) {
	auto it = std::find(v.begin(), v.end(), x);
	if (it != v.end()) {
		return std::distance(v.begin(), it);
	}
	//means that the find is unsuccessful
	return -1;
}
//b)
template<typename value_type>
Result find_sequential_greater3(const Vector<value_type>& v, value_type x) {
	//get lower bound iterator
	auto low = std::lower_bound(v.begin(), v.end(), x);
	//get upper bound iterator
	auto up = std::upper_bound(v.begin(), v.end(), x);
	//check if successful
	if (up != v.end()) {
		//get index
		int upindex = std::distance(v.begin(), up);
		int lowindex = std::distance(v.begin(), low);
		//check if more than one value in v equal to x
		if (upindex - lowindex > 1)
			lowindex = upindex - 1;
		//return indexes
		return std::make_tuple(std::make_tuple(lowindex, upindex), true);
	}
	return std::make_tuple(std::make_tuple(999, 999), false);
}
//c)implement std::equal_range
template<typename value_type>
Result find_sequential_greater4(const Vector<value_type>& v, value_type x) {
	auto bounds = std::equal_range(v.begin(), v.end(), x);
	auto first = bounds.first;
	auto second = bounds.second;
	if (second != v.end()) {
		int firstindex = std::distance(v.begin(), first);
		int secondindex = std::distance(v.begin(), second);
		//no value in v equal to x
		if (firstindex == secondindex)
			firstindex--;
		//more than one value of v equal to x
		if (secondindex - firstindex > 1)
			firstindex = secondindex - 1;
		return std::make_tuple(std::make_tuple(firstindex, secondindex), true);
	}
	return std::make_tuple(std::make_tuple(999, 999), false);
}

int main() {
	//test the given implementation
	Vector<double> v{ 1,2,2,3,4,5 };
	auto tuple=find_sequential_greater<double>(v, 2);
	auto t = find_sequential_greater<double>(v, 3);
	//check if successful
	if (std::get<1>(tuple) && std::get<1>(t)) {
		//print out first index and second index with different parameters
		auto temp = std::get<0>(tuple);
		std::cout << "with parameter 2: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
		temp = std::get<0>(t);
		std::cout << "with parameter 3: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
	}
	
	//test find_sequential_greater2
	tuple = find_sequential_greater2<double>(v, 2);
	t = find_sequential_greater2<double>(v, 3);
	//check if successful
	if (std::get<1>(tuple) && std::get<1>(t)) {
		//print out first index and second index with different parameters
		auto temp = std::get<0>(tuple);
		std::cout << "with parameter 2: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
		temp = std::get<0>(t);
		std::cout << "with parameter 3: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
	}
	
	//check find_index
	std::cout << "check find index with parameter 2: ";
	std::cout << find_index<double>(v, 2) << std::endl;
	
	//test find_sequential_greater3
	tuple = find_sequential_greater3<double>(v, 2);
	t = find_sequential_greater3<double>(v, 3);
	//check if successful
	if (std::get<1>(tuple) && std::get<1>(t)) {
		//print out first index and second index with different parameters
		auto temp = std::get<0>(tuple);
		std::cout << "with parameter 2: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
		temp = std::get<0>(t);
		std::cout << "with parameter 3: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
	}

	//test find_sequential_greater4
	tuple = find_sequential_greater4<double>(v, 2);
	t = find_sequential_greater4<double>(v, 3);
	//check if successful
	if (std::get<1>(tuple) && std::get<1>(t)) {
		//print out first index and second index with different parameters
		auto temp = std::get<0>(tuple);
		std::cout << "with parameter 2: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
		temp = std::get<0>(t);
		std::cout << "with parameter 3: " << std::get<0>(temp) << "--" << std::get<1>(temp) << std::endl;
	}

	//d)test find_if_not
	auto it = std::find_if_not(v.begin(), v.end(), [](double x) {return x < 2; });
	std::cout << "for d: " << *it << std::endl;
	return 0;
}