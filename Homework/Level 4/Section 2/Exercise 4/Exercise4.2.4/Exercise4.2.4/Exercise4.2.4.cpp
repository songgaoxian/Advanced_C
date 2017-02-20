//Exercise4.2.4
//
//apply sregex_token_iterator
//written on 2016/6/18

#include<string>
#include<iostream>
#include<regex>
#include<vector>
#include<boost/lexical_cast.hpp>

int main() {
	std::regex myReg10("/");
	std::string S3 = "2016/3/15";
    //to store 2016, 3 and 15
	std::vector<int> iv;
	//to store "/"
	std::vector<std::string> sv;

	//a)extract 2016,3, and 15
	std::sregex_token_iterator stit(S3.begin(), S3.end(), myReg10, -1);
	std::sregex_token_iterator end;
	while (stit != end) {
		//get the extracted string
		std::string s = *stit;
		//convert to int and push to iv
		iv.push_back(boost::lexical_cast<int>(s));
		//increment stit
		++stit;
	}

	//b)extract "/"
	std::sregex_token_iterator stit2(S3.begin(), S3.end(), myReg10, 0);
	while (stit2 != end) {
		//get extracted string
		std::string s = *stit2;
		//push s to sv
		sv.push_back(s);
		//increment stit2
		stit2++;
	}

	//display
	std::cout << "Display int from string S3:\n";
	for (auto it = iv.begin(); it != iv.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
	std::cout << "Display string from string S3:\n";
	for (auto it = sv.begin(); it != sv.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
	return 0;

}