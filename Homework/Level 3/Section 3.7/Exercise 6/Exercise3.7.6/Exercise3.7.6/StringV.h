#ifndef StringV_H
#define StringV_H
#include<vector>
#include<stdio.h>
#include<ctype.h>
#include<string>
#include<algorithm>
#include<functional>
#include<iostream>

using stringV = std::vector<char>;
//trim leading and trailing blanks
stringV& trim(stringV& sv) {
	//find first element's position with nonspace character
	auto iter = std::find_if_not(sv.begin(), sv.end(), isspace);
	//trim leading blanks
	sv=stringV(iter, sv.end());
	//reverse sv
	std::reverse(sv.begin(), sv.end());
	//find first non space character
	auto iter2 = std::find_if_not(sv.begin(), sv.end(), isspace);
	sv = stringV(iter2, sv.end());
    //reverse sv
	std::reverse(sv.begin(), sv.end());
	return sv;
}
//trim if
using Predicate = std::function<bool(char)>;

bool ifspace(char val) {
	if (val == '\t' || val == ' ')
		return true;
	else
		return false;
}

stringV& trim_if(stringV& sv, Predicate p) {
	//find first element's position with nonspace character
	auto iter = std::find_if_not(sv.begin(), sv.end(), p);
	//trim leading blanks
	sv = stringV(iter, sv.end());
	//reverse sv
	std::reverse(sv.begin(), sv.end());
	//find first non space character
	auto iter2 = std::find_if_not(sv.begin(), sv.end(), p);
	sv = stringV(iter2, sv.end());
	//reverse sv
	std::reverse(sv.begin(), sv.end());
	return sv;
}
//produce a vector of string from character-separated string
stringV getStringV(char* s){
	int index = 0;
	stringV sv;
	//push characters to sv
	while (s[index] != '\0') {
		sv.push_back(s[index]);
		index++;
	}
	return sv;
}
//join two strings
stringV join(stringV& sv1, stringV& sv2) {
	//initialise the result string
	stringV result(sv1.size() + sv2.size());
	//copy sv1 to result
	auto it = std::copy(sv1.begin(), sv1.end(), result.begin());
	//copy sv2 to result
	std::copy(sv2.begin(), sv2.end(), it);
	return result;
}


#endif
