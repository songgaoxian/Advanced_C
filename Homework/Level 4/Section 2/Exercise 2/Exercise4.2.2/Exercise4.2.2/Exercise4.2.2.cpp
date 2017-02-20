//Exercise4.2.2
//
//apply regex_search
//written on 2016/6/18

#include<iostream>
#include<regex>
#include<string>

int main() {
	std::regex mySearchReg("(rain)|(Spain)");
	//target string
	std::string myText("The rain in Spain stays mainly on the plain");
	std::smatch what;
	//search
	if (!std::regex_search(myText, what, mySearchReg)) {
		std::cout << "no match is found\n";
	}
	else {
		//print out all searched matches
		do {
			std::cout << "match is found\n";
			//display contents of match
			for (auto x : what) std::cout << x << " ";
			std::cout << '\n';
			//reset myText to be the sequence following the previous match
			myText = what.suffix().str();
		} while (std::regex_search(myText, what, mySearchReg));
	}
	return 0;
}