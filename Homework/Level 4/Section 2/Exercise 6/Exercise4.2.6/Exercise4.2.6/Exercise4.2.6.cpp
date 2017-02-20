//Exercise4.2.6
//
//exercise to apply ECMAScript grammar
//written on 2016/6/19

#include<regex>
#include<string>
#include<iostream>
#include<boost/lexical_cast.hpp>

bool test_num(std::string& num){
	//copied
	std::regex ecmaReg("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
	//check if match
	return std::regex_match(num, ecmaReg);
}


int main() {
	//a)
	//it supports numbers with or without positive/negative sign followed by
	//1 or more digits; optionally, the number can be further followed by '.' and 
	//1 or more digits; optionally, the number can be further followed by e or E 
	// and 1 or more digits, in front of which can have or not have positive or
	//negative sign;

	//valid numbers format
	std::string snum("123");
	std::string snum2("-12.339E3");
	std::string snum3("+88.99");
	std::string snum4("77e-4");
	//invalid numbers format
	std::string snum5("123u");
	std::string snum6("333ul");
	std::string snum7("9.1f");

	//test valid and invalid numbers and convert valid numbers
	std::boolalpha(std::cout);
	//test snum
	if (test_num(snum)) {
		std::cout << "snum is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum is not valid\n";
	}

	//test snum2
	if (test_num(snum2)) {
		std::cout << "snum2 is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum2);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum2 is not valid\n";
	}

	//test snum3
	if (test_num(snum3)) {
		std::cout << "snum3 is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum3);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum3 is not valid\n";
	}

	//test snum4
	if (test_num(snum4)) {
		std::cout << "snum4 is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum4);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum4 is not valid\n";
	}

	//test snum5
	if (test_num(snum5)) {
		std::cout << "snum5 is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum5);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum5 is not valid\n";
	}

	//test snum6
	if (test_num(snum6)) {
		std::cout << "snum6 is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum6);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum6 is not valid\n";
	}

	//test snum7
	if (test_num(snum7)) {
		std::cout << "snum7 is valid with value=";
		//convert to double
		double num = boost::lexical_cast<double>(snum7);
		std::cout << num << '\n';
	}
	else {
		std::cout << "snum7 is not valid\n";
	}

	return 0;
}