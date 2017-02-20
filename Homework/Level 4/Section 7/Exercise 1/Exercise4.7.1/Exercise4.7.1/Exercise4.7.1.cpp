//Exercise4.7.1
//
//apply syntax of bimap
//written on 2016/6/21

#include<boost/bimap.hpp>
#include<string>
#include<iostream>
#include<utility>
#include<map>

template<class MapType>
void print(const MapType& map) {
	//print map content
	for (auto it = map.begin(); it != map.end(); it++) {
		std::cout << "(" << it->first << "," << it->second << ") ";
	}
	std::cout << '\n';
}

int main() {
	boost::bimap<std::string, int> p_bimap1, p_bimap2;
	//a)
	using person = boost::bimap<std::string, int>::value_type;
	//use insert
	p_bimap1.insert(person("Michaelle", 25));
	p_bimap1.insert(person("LittleSeal", 2));
	p_bimap1.insert(person("Baochang", 86));
	//try emplace
	//p_bimap2.emplace("Michaelle", 25);//not working
	
	//b)
	std::cout << "Print left maps:\n";
	print(p_bimap1.left);
	std::cout << "Print right maps:\n";
	print(p_bimap1.right);

	//c)
	//search age based on name
	std::cout << "Search age based on name:\n";
	try {
		//set name to be search basis
		std::string name = "LittleSeal";
		std::cout << "search age for " << name << ": ";
		//search age based on name
		int age = p_bimap1.left.at(name);
		std::cout << "age is " << age << '\n';

		//set another name
		name = "notExist";
		std::cout << "search age for " << name << ": ";
		//search age based on name
		age = p_bimap1.left.at(name);
		std::cout << "age is " << age << '\n';
	}
	catch (...) { std::cout << "not found\n"; }

	//search name based on age
	std::cout << "Search name based on age:\n";
	try {
		//set age to be search basis
		int age = 2;
		std::cout << "search name for age " << age << ": ";
		//search name based on age
		std::string name = p_bimap1.right.at(age);
		std::cout << "name is " << name << '\n';

		//set age 
		age = 222;
		std::cout << "search name for age " << age << ": ";
		//search name based on age
		name = p_bimap1.right.at(age);
		std::cout << "name is " << name << '\n';
	}
	catch (...) { std::cout << "not found\n"; }

	//d)
	std::cout << "\nIterate p_bimap1 using third view:\n";
	//iterate
	for (auto it = p_bimap1.begin(); it != p_bimap1.end(); ++it) {
		std::cout << "Name is " << it->left << ", age is " << it->right << '\n';
	}

	return 0;
}