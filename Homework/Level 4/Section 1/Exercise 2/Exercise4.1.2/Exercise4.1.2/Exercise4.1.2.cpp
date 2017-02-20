//Exercise4.1.2
//
//exercise to apply string algo to test characteristics of string sequence
//written on 2016/6/18

#include<boost/algorithm/string.hpp>
#include<string>
#include<iostream>
#include<tuple>

//test password
std::tuple<bool, std::string> check_password(std::string& pswd) {
	//check length
	if (pswd.length() < 8) {
		return std::make_tuple<bool, std::string>(false, "password need to at least 8 chars");
	}

	//check digits and characters
	//get the result if contain digits
	bool containDigits = std::any_of(pswd.begin(), pswd.end(), boost::algorithm::is_digit());
	//get the result if contain char
	bool containChar = std::any_of(pswd.begin(), pswd.end(), boost::algorithm::is_alpha());
	bool containBoth = (containChar && containDigits);
	if(!containBoth){
		return std::make_tuple(false, "password must contain both digits and chars");
	}

	//check if contain upper case character
	//if all elements of pswd are not upper case, return false
	if (boost::algorithm::all(pswd, !boost::algorithm::is_upper())) {
		return std::make_tuple(false, "At least one character must be upper case");
	}

	//check that there not exist control chars
	bool noControl = boost::algorithm::all(pswd, !boost::algorithm::is_cntrl());
	if (!noControl) {
		return std::make_tuple(false, "no control characters allowed");
	}

	//check if there exists space
	bool noSpace = boost::algorithm::all(pswd, !boost::algorithm::is_space());
	if (!noSpace) {
		return std::make_tuple(false, "no space is allowed");
	}

	return std::make_tuple(true, "a valid password created");
}


int main() {
	std::boolalpha(std::cout);
	//a)
	std::cout << "a)\n";
	std::string str1("   abd1 234\*");
	//use P1
	std::cout <<"Is str1 all digits or letters? "<< boost::algorithm::all(str1, (boost::algorithm::is_digit()) || (boost::algorithm::is_alpha()))<<'\n';
	//use P2
	std::cout << "Is str1 all digits and not letters? " << boost::algorithm::all(str1, (boost::algorithm::is_digit()) && (!boost::algorithm::is_alpha())) << '\n';
	//use P3
	std::cout << "Is str1 all in the range a to z? " << boost::algorithm::all(str1, (boost::algorithm::is_alpha()) && (boost::algorithm::is_lower())) << '\n';

	//b)
	std::cout << "\nb)\n";
	//std::string pwd("DanielDuffy1952");
	//std::string pwd("DanielDuffy");
	//std::string pwd("U19520829");
	std::string pwd("19520829U");
	std::cout << "Given password:" << pwd << '\n';
	//check password
	std::tuple<bool, std::string> result = check_password(pwd);
	//display check result
	std::cout << "Does a password pass the test? " << std::get<0>(result) << '\n';
	std::cout << std::get<1>(result) << '\n';


	return 0;
}