#include<bitset>
#include<string>
#include<iostream>


int main() {
	//a)
	//create unsigned long and usigned long long variables
	unsigned long ul1 = 10;
	unsigned long long ull1 = 100;
	//set number of bits to 15
	const std::size_t N = 15;
	//create bitset for ul1
	std::bitset<N> bs1(ul1);
	//create bitset for ull1
	std::bitset<N> bs2(ull1);
	//print out
	std::cout << "a):\n" << "bs1=" << bs1 << "; bs2=" << bs2 << std::endl;
	//end of a)

	//b)
	//create bitset from string
	std::bitset<N> bs3(std::string("10100100101"));
	//create bitset from parts of string
	int startindex = 3; //where to start
	int num = 4; //specify how many bits
	std::bitset<N> bs4(std::string("10100100101"), startindex, num);
	//print out
	std::cout << "b):\n" << "bs3=" << bs3 << "; bs4=" << bs4 << std::endl;
	//end of b)

	//c) exception handling in bitset
	try {
		errno = 0;
		std::cout << "try invalid arguments\n";
		//provide a string s which is invalid for bitset
		std::string s("123456");
		//create a bitset with invalid string
		std::bitset<N> bs5(s);
	}
	catch (...) {
		std::cout << "invalid argument\n";
	}
	try {
		std::cout << "try out of range values\n";
		//create a bitset which throws out of range exception
		int index = 13;
		int num_bit = 10;
		std::bitset<N> bs6(std::string("1001001001"),index,num_bit);
	}
	catch (...) {
		std::cout <<"out of range\n";
	}
	//end of c)

	//d)
	//set all bits
	bs1.set();
	std::cout << "d):\n" << "after set, bs1=" << bs1 << std::endl;
	//reset all bits
	bs2.reset();
	std::cout << "after reset, bs2=" << bs2 << std::endl;
	//flip bits
	bs3.flip();
	std::cout << "after flip, bs3=" << bs3 << std::endl;
	//toggle bit at possition 2
	bs3.flip(2);
	std::cout << "after flip(2), bs3=" << bs3 << std::endl;
	//test if any bits are set
	if (bs4.any()) {
		std::cout << "\nbs4 has bits set\n";
	}
	else {
		std::cout << "\nbs4 has no bit set\n";
	}
	//test if non bit is set
	if (bs2.none()) {
		std::cout << "\nbs2 has no set bit\n";
	}
	else {
		std::cout << "\nbs2 has bits set\n";
	}
	//access elements
	bs2[0] = 1;
	std::cout << "bs2[0]: " << bs2[0] << std::endl;
	std::cout << "bs2: " << bs2 << std::endl;
	//count number of set bits
	std::cout << "bs2 number of set bits: " << bs2.count() << std::endl;
	//end of d)

	//e)
	//convert bs4 to string
	std::string s4 = bs4.to_string();
	std::cout << "e):\ns4=" << s4 << std::endl;
	//convert bs4 to unsigned long
	unsigned long ulc = bs4.to_ulong();
	std::cout << "ulc from bs4: " << ulc << std::endl;
	//convert bs4 to unsigned long long
	unsigned long long ullc = bs4.to_ullong();
	std::cout << "ullc from bs4: " << ullc << std::endl;
	//end of e)

	//f)
	//test if bs4 and bs3 are equal
	if (bs4 == bs3) {
		std::cout << "bs4 is same as bs3\n";
	}
	if (bs4 != bs3) {
		std::cout << "bs4 differs from bs3\n";
	}
	//end of f)

	return 0;
}