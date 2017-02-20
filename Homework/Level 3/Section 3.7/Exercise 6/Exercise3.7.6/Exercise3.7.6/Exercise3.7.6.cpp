#include<set>
#include<algorithm>
#include<functional>
#include<iostream>
#include<array>
#include<vector>
#include"Point.h"
#include "StringV.h"



int main() {
	//a)
	//provide first set
	std::set<char> s1{ 'a','b','c','d','e','k' };
	//provide second set
	std::set<char> s2{ 'a','e' };
	std::set<char> s3;
    //apply set-difference
	std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(s3,s3.begin()));
	//print out current set s1
	for (auto it = s3.begin(); it != s3.end(); it++)
		std::cout << *it << " ";


	//b)
	std::cout << '\n';
	const int N = 6;
	std::array<Point, N> arr{ Point(1,0),Point(4,5),Point(5,5),Point(1,0),Point(2,3),Point(1,0) };
	//sort arr
	std::sort(arr.begin(), arr.end(), Less());
	//print out arr
	std::cout << "original sorted set:\n";
	std::for_each(arr.begin(), arr.end(), [](Point p) {
		std::cout << "(" << p.X() << ", " << p.Y() << ") ";
	});
	std::cout << "\n";
	
	//remove duplicates 
	auto iterb = std::unique(arr.begin(), arr.end(), IsEqual);
	//store duplicate-free points in a set
	std::set<Point,Less> vp(arr.begin(), iterb);
	//print out duplicate-free set
	std::cout << "duplicate-free set:\n";
	for (auto itb = vp.begin(); itb != vp.end(); itb++)
		std::cout << "(" << (*itb).X() << ", " << (*itb).Y() << ") ";
	std::cout << '\n';
	
	double thresh = 4;
	Point centre(0, 0);
	//to store filtered points
	std::set<Point, Less> finalSet;
	//only copy points within distance
	std::copy_if(vp.begin(), vp.end(), std::inserter(finalSet, finalSet.begin()),std::bind(WithinDistance,centre,thresh,std::placeholders::_1));
	//print out final set
	std::cout << "Within distance set:\n";
	std::for_each(finalSet.begin(), finalSet.end(), [](const Point& p) {
		std::cout << "(" << p.X() << ", " << p.Y() << ") ";
	});
	std::cout << '\n';

	//c)
	stringV sv1{ '\t',' ','a','b','\t',' ','c','\t',' ' };
	stringV sv2(sv1);
	char charstring[] = "hello";
	//use trim to remove blanks
	sv1 = trim(sv1);
	//print out sv1
	std::cout << "after trime:\n";
	std::for_each(sv1.begin(), sv1.end(), [](char val) {
		std::cout << val << ' ';
	});
	std::cout << '\n';

	//use trim_if
	sv2 = trim_if(sv2, ifspace);
	std::cout << "after trim_if:\n";
	std::for_each(sv2.begin(), sv2.end(), [](char val) {
		std::cout << val << ' ';
	});
	std::cout << '\n';

	//produce vector of string 
	stringV sv3=getStringV(charstring);
	std::cout << "produce vector of string\n";
	std::for_each(sv3.begin(), sv3.end(), [](char val) {
		std::cout << val << ' ';
	});
	std::cout << '\n';

	//join two string
	stringV sv4 = join(sv3, sv2);
	std::cout << "join strings\n";
	std::for_each(sv4.begin(), sv4.end(), [](char val) {
		std::cout << val << ' ';
	});
	std::cout << '\n';

	return 0;
}