//Exercise4.2.5
//
//extract name-value pairs using regex and string algo
//written on 2016/6/18

#include<regex>
#include<string>
#include<iostream>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include<vector>
#include<map>

int main() {
	//string to be considered
	std::string sA("a=1, b=2, c=3, qq=99");
	//a)
	//define the regular expression
	std::regex myReg(",");
	//use token_iterator to extract "a=1" etc
	std::sregex_token_iterator sregIt(sA.begin(), sA.end(), myReg, -1);
	std::sregex_token_iterator end;

	//b)
	//to store chars as key and int as value
	std::map<std::string, int> result; 
	for (auto it = sregIt; it != end; it++) {
		std::string s = *it;
		//store splited string
		std::vector<std::string> split_string;
		//split s
		boost::algorithm::split(split_string, s, boost::algorithm::is_any_of("="));
		//trim blanks
		boost::algorithm::trim(split_string[0]);
		boost::algorithm::trim_right(split_string[0]);
		boost::algorithm::trim(split_string[1]);
		boost::algorithm::trim_right(split_string[1]);
		//put key and value into map
		result[split_string[0]] = boost::lexical_cast<int>(split_string[1]);
		split_string.clear();
	}

	//print out result
	for (auto it = result.begin(); it != result.end(); it++) {
		std::cout << it->first << ": " << it->second << '\n';
	}

	return 0;
}