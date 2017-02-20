//Exercise4.2.7
//
//apply sregex_replace
//written on 2016/6/19

#include<regex>
#include<string>
#include<iostream>

int main() {
	std::string text("Quick brown fox");
	std::regex vowels("a|e|i|o|u");
	//result to be "Q**ck br*wn f*x"
	std::string result;
	result=std::regex_replace(text, vowels, "*$1");
	std::cout << result << '\n';
	return 0;
}