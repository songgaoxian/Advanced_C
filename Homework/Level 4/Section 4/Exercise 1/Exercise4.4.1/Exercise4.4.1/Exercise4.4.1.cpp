//Exercise4.4.1
//
//apply hash in boost and c++
//written on 2016/6/20


#include<functional>
#include<boost/functional/hash.hpp>
#include<string>
#include<climits>
#include<iostream>
//a)
//use std::hash to hash arbitrary data types
template<typename value_type>
std::size_t hash_std(const value_type& data) {
	std::hash<value_type> hash;
	return hash(data);
}
//use boost::hash to hash aribtrary data types
template<typename value_type>
std::size_t hash_boost(const value_type& data) {
	boost::hash<value_type> hash;
	return hash(data);
}

int main() {
	//b)
	//variables to test two functions
	int num1 = 10, num2 = 9;
	std::string s1("hello"), s2("hello"),s3("world");
	int* pt1,* pt2;
	pt1 =&num1;
	pt2 =&num2;
	long numLong = std::numeric_limits<long>::max();
	//test variables
	//test integers
	std::cout << "for num1:std hash=" << hash_std<int>(num1) << ", boost hash=" << hash_boost<int>(num1) << '\n';
	std::cout << "for num2:std hash=" << hash_std<int>(num2) << ", boost hash=" << hash_boost<int>(num2) << '\n';
	//test strings
	std::cout << "for s1:std hash=" << hash_std<std::string>(s1) << ", boost hash=" << hash_boost<std::string>(s2) << '\n';
	std::cout << "for s2:std hash=" << hash_std<std::string>(s2) << ", boost hash=" << hash_boost<std::string>(s2) << '\n';
	//test pointers
	std::cout << "for pt1:std hash=" << hash_std<int*>(pt1) << ", boost hash=" << hash_boost<int*>(pt1) << '\n';
	std::cout << "for pt2:std hash=" << hash_std<int*>(pt2) << ", boost hash=" << hash_boost<int*>(pt2) << '\n';
	//test numLong
	std::cout << "for numLong:std hash=" << hash_std<long>(numLong) << ", boost hash=" << hash_boost<long>(numLong) << '\n';

	//c)
	//create two hashes 
	std::hash<std::string> hash1;
	std::hash<std::string> hash2;
	//get hashes of strings
	std::size_t h1 = hash1(s1);
	std::size_t h2 = hash2(s3);
    //compute result
	auto result = (h1 ^ (h2 << 1));
	std::cout << "Result of c):" << result << '\n';

	return 0;
}