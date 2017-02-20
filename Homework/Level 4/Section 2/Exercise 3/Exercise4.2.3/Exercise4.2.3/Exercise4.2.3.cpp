//Exercise4.2.3
//
//exercise to use sregex_iterator
//written on 2016/6/18

#include<regex>
#include<iostream>
#include<string>
#include<set>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>

int main() {
	//modify code
	//std::set<std::string> result;
	std::set<int> result;
	std::string S2 = "1,1,2,3,5,8,13,21";
	std::regex myReg("(\\d+),?");
	//a)
	//create it, an instance of sregex_iterator
	std::sregex_iterator it(S2.begin(), S2.end(), myReg);
	std::sregex_iterator end;

	//b)
	//iterate over
	for (auto iter = it; iter != end; iter++) {
		//dereference iter
		std::smatch what = *iter;
		//convert to string
		std::string str = what.str();
		//modify code for d)
		//trim ,
		boost::algorithm::trim_right_if(str,boost::algorithm::is_any_of(","));
		//convert to int
		int num = boost::lexical_cast<int>(str);
		//insert to result
		//result.insert(str);//modify for d)
		result.insert(num);
	}

	//c)print it
	std::cout << "sregex_iterator version:\n";
	while (it != end) {
		std::cout << (*it).str() << ' ';
		it++;
	}

	//print out result
	std::cout << "\nset version:\n";
	for(auto sit = result.begin(); sit != result.end(); sit++)
		std::cout << *sit << ' ';

	return 0;

}