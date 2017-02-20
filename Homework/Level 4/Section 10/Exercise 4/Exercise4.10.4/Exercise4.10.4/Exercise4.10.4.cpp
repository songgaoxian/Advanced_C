//Exercise4.10.4
//
//use uBlas and STL
//written on 2016/6/24

#include<boost\numeric\ublas\vector.hpp>
#include<boost\numeric\ublas\io.hpp>
#include<tuple>
#include<iostream>
#include<algorithm>
#include<complex>

using Range = std::tuple<std::size_t, std::size_t>;
using Result = std::tuple<Range, bool>;

using value_type = double;
using Vector = boost::numeric::ublas::vector<value_type>;


Result find_sequential_greater(const Vector& v, value_type x) {
	for (std::size_t j = 0; j < v.size(); ++j) {
		if (v[j] <= x && v[j + 1] > x) {
			return std::make_tuple(std::make_tuple(j, j + 1), true);
		}
	}

	return std::make_tuple(std::make_tuple(999, 999), false);
}

//a)implement same functionality with find_if
Result find_sequential_greater2(const Vector& v, value_type x) {
	auto greater = [x](value_type val) {return val > x; };

	//apply find_if
	auto it_a = std::find_if(v.begin(), v.end(), greater);
	int index = std::distance(v.begin(), it_a);
	//get result
	Result result_a;
	if (it_a != v.end()) {
		result_a = std::make_tuple(std::make_tuple(index - 1, index), true);
	}
	else {
		result_a = std::make_tuple(std::make_tuple(999, 999), false);
	}
	return result_a;
}

//find a given value
int find(const Vector& v, value_type x) {
	auto it = std::find(v.begin(), v.end(), x);
	if (it != v.end()) {
		return std::distance(v.begin(), it);
	}
	else {
		return -1; //means that no match is found
	}
}

//b)use lower_bound and upper_bound
Result find_sequential_greater3(const Vector& v, value_type x) {
	//define predicates
	auto less = [](value_type x,value_type val) {return x < val; };
	//get lower and upper bound iterator
	auto lower_it = std::lower_bound(v.begin(), v.end(), x, less);
	auto upper_it = std::upper_bound(v.begin(), v.end(), x, less);
	//convert to int
	int lower = std::distance(v.begin(), lower_it);
	int upper = std::distance(v.begin(), upper_it);
	//check if exist match
	if (upper_it != v.end()) {
		if (upper - lower > 1) lower = upper - 1;
		return std::make_tuple(std::make_tuple(lower, upper), true);
	}
	else {
		return std::make_tuple(std::make_tuple(999, 999), false);
	}
}

//c)use equal_range
Result find_sequential_greater4(const Vector& v, value_type x) {
	//define predicate
	auto less = [](value_type x, value_type val) {return x < val; };
	auto bounds = std::equal_range(v.begin(), v.end(), x, less);
	//get first and second iterator
	auto it_first = bounds.first;
	auto it_second = bounds.second;
	//convert to integers
	int first = std::distance(v.begin(), it_first);
	int second = std::distance(v.begin(), it_second);
	//check if exist match
	if (it_second != v.end()) {
		if (second - first > 1) first = second - 1;
		return std::make_tuple(std::make_tuple(first, second), true);
	}
	else {
		return std::make_tuple(std::make_tuple(999, 999), false);
	}
}

int main() {
	//a)
	std::cout << "a)\n";
	//create Vector
	Vector v(5);
	v[0] = 0.5;
	v[1] = 2.5;
	v[2] = 2.0;
	v[3] = 1.9;
	v[4] = 2.0;
	//sort v
	std::sort(v.begin(), v.end());
	
	//define predicate
	value_type x = 2.0;
	Result r1 = find_sequential_greater(v, x);
	Result r2 = find_sequential_greater2(v, x);

	std::boolalpha(std::cout);
	//print out r1
	std::cout << "use find_sequential_greater for x=" << x << ":\n";
	std::cout << "find x? " << std::get<1>(r1) << '\n';
	std::tuple<std::size_t, std::size_t> position = std::get<0>(r1);
	std::cout << "position index1=" << std::get<0>(position) << ", position index2=" << std::get<1>(position) << '\n';

	//print out r2
	std::cout << "use find_sequential_greater2 for x=" << x << ":\n";
	std::cout << "find x? " << std::get<1>(r2) << '\n';
	position = std::get<0>(r2);
	std::cout << "position index1=" << std::get<0>(position) << ", position index2=" << std::get<1>(position) << '\n';
	
	x = 1.9;
	std::cout << "where is x=" << x << "? It is positioned at " << find(v, x) << '\n';

	//b)
	x = 2.0;
	std::cout << "\nb)\nuse find_sequential_greater3 for x=" << x << ":\n";
	r1 = find_sequential_greater3(v, x);
	position = std::get<0>(r1);
	//print out r1
	std::cout << "find x? " << std::get<1>(r1) << '\n';
	std::cout << "position index1=" << std::get<0>(position) << ", position index2=" << std::get<1>(position) << '\n';

	//c)
	std::cout << "\nc)\nuse find_sequential_greater4 for x=" << x << ":\n";
	r1 = find_sequential_greater4(v, x);
	position = std::get<0>(r1);
	//print out r1
	std::cout << "find x? " << std::get<1>(r1) << '\n';
	std::cout << "position index1=" << std::get<0>(position) << ", position index2=" << std::get<1>(position) << '\n';

	//d)
	//define predicate
	auto lessThan1 = [](value_type val) {return val < 1; };
	auto it = std::find_if_not(v.begin(), v.end(), lessThan1);
	std::cout << "\nd)\noutput from find_if_not: *it=" << *it << ", index=" << std::distance(v.begin(), it) << '\n';

	return 0;


}