//Exercise4.2.1
//
//apply regex_match
//written on 2016/6/18

#include<regex>
#include<iostream>
#include<string>
#include<boost/regex.hpp>

int main() {
	//a)
	std::cout << "a)\n";
	std::regex myReg("[a-z]*");//zero or more chars
	std::regex myReg2("[a-z]+");//one or more chars

	//strings to be tested
	std::string s1("aza");
	std::string s2("1");
	std::string s3("b");
	std::string s4("ZZ TOP");

	std::boolalpha(std::cout);
	//test with myReg
	std::cout << "Does s1 match myReg? " << std::regex_match(s1, myReg) << '\n';
	std::cout << "Does s2 match myReg? " << std::regex_match(s2, myReg) << '\n';
	std::cout << "Does s3 match myReg? " << std::regex_match(s3, myReg) << '\n';
	std::cout << "Does s4 match myReg? " << std::regex_match(s4, myReg) << '\n';

	//test with myReg2
	std::cout << "Does s1 match myReg2? " << std::regex_match(s1, myReg2) << '\n';
	std::cout << "Does s2 match myReg2? " << std::regex_match(s2, myReg2) << '\n';
	std::cout << "Does s3 match myReg2? " << std::regex_match(s3, myReg2) << '\n';
	std::cout << "Does s4 match myReg2? " << std::regex_match(s4, myReg2) << '\n';

	//b)
	std::cout << "\nb)\n";
	std::regex myNumericReg("\\d{2}");//two digits
	std::string f("34");
	std::string s("345");

	//test 
	std::cout << "Does f match myNumericReg? " << std::regex_match(f, myNumericReg) << '\n';
	std::cout << "Does s match myNumericReg? " << std::regex_match(s, myNumericReg) << '\n';

	//c
	std::cout << "\nc)\n";
	std::regex myAltReg("(new) | (delete)");//only new or delete pass
	std::string s4A("new");
	std::string s5("delete");
	std::string s6("malloc");

	//test
	std::cout << "Does s4A match myAltReg? " << std::regex_match(s4A, myAltReg) << '\n';
	std::cout << "Does s5 match myAltReg? " << std::regex_match(s5, myAltReg) << '\n';
	std::cout << "Does s6 match myAltReg? " << std::regex_match(s6, myAltReg) << '\n';

	//d)
	std::cout << "\nd)\n";
	std::regex myReg3("A*"); //0 or more A
	std::regex myReg4("A+");//1 or more A
	std::regex myReg5("(\\d{2})");//2 consecutive digits
	std::regex myReg6("\\d{2,4}");//2 to 4 digits
	std::regex myReg7("\\d{1,}");//1 or more digits

	std::string testA("1");
	
	//test
	std::cout << "Does testA match myReg3? " << std::regex_match(testA, myReg3) << '\n';
	std::cout << "Does testA match myReg4? " << std::regex_match(testA, myReg4) << '\n';
	std::cout << "Does testA match myReg5? " << std::regex_match(testA, myReg5) << '\n';
	std::cout << "Does testA match myReg6? " << std::regex_match(testA, myReg6) << '\n';
	std::cout << "Does testA match myReg7? " << std::regex_match(testA, myReg7) << '\n';

	//e)
	std::cout << "\ne)\n";
	std::regex rC("(\\w)*");//word
	std::regex rC1("(\\W)*");//not a word
	std::regex rC2("[A-Za-z0-9_]*");//word

	std::string sC1("abc");
	std::string sC2("A12678Z909za");

	//test rC
	std::cout << "Does sC1 match rC? " << std::regex_match(sC1, rC) << '\n';
	std::cout << "Does sC2 match rC? " << std::regex_match(sC2, rC) << '\n';
	//test rC1
	std::cout << "Does sC1 match rC1? " << std::regex_match(sC1, rC1) << '\n';
	std::cout << "Does sC2 match rC1? " << std::regex_match(sC2, rC1) << '\n';
	//test rC2
	std::cout << "Does sC1 match rC2? " << std::regex_match(sC1, rC2) << '\n';
	std::cout << "Does sC2 match rC2? " << std::regex_match(sC2, rC2) << '\n';

	//extra example
	//ECMA
	std::regex extraReg("(5{2})", std::regex::ECMAScript|std::regex::icase);
	std::regex extraReg2("\\D*", std::regex::ECMAScript);
	//Perl
	boost::regex extraReg3("^a{2,4}b{3,}$", boost::regex::perl|boost::regex::icase);
	//extra strings
	std::string str("55"), str1("5555"); //to test with extraReg
	std::string str2(""), str3("abc"), str4("123"); //to test with extraReg2
	std::string str5("aAb"), str6("aaABbbbb");//to test with extraReg3

	std::cout << "\nextra)\n";
	//test with extraReg
	std::cout << "Does str match with extraReg? " << std::regex_match(str, extraReg) << '\n';
	std::cout << "Does str1 match with extraReg? " << std::regex_match(str1, extraReg) << '\n';
	//test with extraReg2
	std::cout << "Does str2 match with extraReg2? " << std::regex_match(str2, extraReg2) << '\n';
	std::cout << "Does str3 match with extraReg2? " << std::regex_match(str3, extraReg2) << '\n';
	std::cout << "Does str4 match with extraReg2? " << std::regex_match(str4, extraReg2) << '\n';
	//test with extraReg3
	std::cout << "Does str5 match with extraReg3? " << boost::regex_match(str5, extraReg3) << '\n';
	std::cout << "Does str6 match with extraReg3? " << boost::regex_match(str6, extraReg3) << '\n';



	return 0;
	


}