#include<bitset>
#include<string>
#include<iostream>
#include<exception>
#include<boost/dynamic_bitset.hpp>
#include<boost/functional/hash.hpp>
#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS

int main() {
	//a)
	//port code from exercise2.8.1
	{
		std::cout << "2.8.1\n";
		unsigned long ul1 = 10;
		unsigned long long ull1 = 100;
		//set number of bits to 15
		const std::size_t N = 15;
		//create bitset for ul1
		boost::dynamic_bitset<unsigned long> bs11(N, ul1);
		//create bitset for ull1
		boost::dynamic_bitset<unsigned long long> bs12(N, ull1);
		//print out
		std::cout << "a):\n" << "bs11=" << bs11 << "; bs12=" << bs12 << std::endl;

		//create bitset from string
		boost::dynamic_bitset<unsigned char> bs3(std::string("10100100101"));
		//create bitset from parts of string
		int startindex = 3; //where to start
		int num = 4; //specify how many bits
		boost::dynamic_bitset<unsigned char> bs4(std::string("10100100101"), startindex, num);
		//print out
		std::cout << "b):\n" << "bs3=" << bs3 << "; bs4=" << bs4 << std::endl;

		//set all bits
		bs11.set();
		std::cout << "d):\n" << "after set, bs11=" << bs11 << std::endl;
		//reset all bits
		bs12.reset();
		std::cout << "after reset, bs12=" << bs12 << std::endl;
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
		if (bs12.none()) {
			std::cout << "\nbs12 has no set bit\n";
		}
		else {
			std::cout << "\nbs12 has bits set\n";
		}
		//access elements
		bs12[0] = 1;
		std::cout << "bs12[0]: " << bs12[0] << std::endl;
		std::cout << "bs12: " << bs12 << std::endl;
		//count number of set bits
		std::cout << "bs12 number of set bits: " << bs12.count() << std::endl;

		//convert bs4 to string
		std::string s4;
		boost::to_string(bs4, s4);
		std::cout << "e):\ns4=" << s4 << std::endl;
		//convert bs4 to unsigned long
		unsigned long ulc = bs4.to_ulong();
		std::cout << "ulc from bs4: " << ulc << std::endl;
		//convert bs4 to unsigned long long

		unsigned long long ullc = (unsigned long long)bs4.to_ulong();
		std::cout << "ullc from bs4: " << ullc << std::endl;

		//test if bs4 and bs3 are equal
		if (bs4 == bs3) {
			std::cout << "bs4 is same as bs3\n";
		}
		if (bs4 != bs3) {
			std::cout << "bs4 differs from bs3\n";
		}
		//end of porting 2.8.1
	}

	
		//2.8.2
		std::cout << "\n2.8.2\n";
		const std::size_t N = 7;
		//create bs1 and bs2 with same size of 7
		boost::dynamic_bitset<unsigned char> bs1(std::string("0010011"));
		boost::dynamic_bitset<unsigned char> bs2(std::string("0110110"));
		//print out bs1 and bs2
		std::cout << "a):\n" << "bs1=" << bs1 << "; bs2=" << bs2 << std::endl;

		//toggle all bits of bs1 and bs2
		bs1.flip();
		bs2.flip();
		//print out bs1 and bs2
		std::cout << "b):\n" << "bs1=" << bs1 << "; bs2=" << bs2 << std::endl;

		//perform XOR without modification
		boost::dynamic_bitset<unsigned char> bsXOR = bs1^bs2;
		std::cout << "c)\n" << "bsXOR=" << bsXOR << std::endl;
		//perform OR with modification
		bs1 |= bs2;
		std::cout << "after OR: bs1=" << bs1 << std::endl;
		//perform AND without modification
		std::cout << "AND on bs1 and bs2: " << (bs1 & bs2) << std::endl;

		int n = 2;//num to shift
				  //shift bs1 to right without modification
		boost::dynamic_bitset<unsigned char> bsRight = (bs1 >> n);
		std::cout << "d)\n" << "bsRight=" << bsRight << std::endl;
		//shift bs2 to left with modification
		bs2 <<= n;
		std::cout << "after left shift, bs2=" << bs2 << std::endl;

		//create hash object
		boost::hash<std::string> bhash;
		//display hashed values
		std::string bstring;
		boost::to_string(bs1, bstring);
		std::cout << "hashed value for bs1: " <<bhash(bstring) << std::endl;
		boost::to_string(bs2, bstring);
		std::cout << "hashed value for bs2: " << bhash(bstring) << std::endl;
		//end of 2.8.2
	//end of a)

	//b)
		const std::size_t n2 = 3;
		//perform resize
		bs1.resize(n2);
		std::cout << "\nbs1.size()=" << bs1.size() << std::endl;
		//perform clear
		bs1.clear();
		std::cout << "after clear, bs1.size()=" << bs1.size() << std::endl;
		//perform push_back
		bs1.push_back(0);
		bs1.push_back(1);
		std::cout << "after push back: bs1[1]=" << bs1[0] << std::endl;
		//perform pop_back
		bs1.pop_back();
		std::cout << "after pop back, bs1.size()=" << bs1.size() << std::endl;
		//perform append
		bs1.append(10);
		std::cout << "after append, bs1=" << bs1 << std::endl;
	//end of b)
	
	//c)
		//create bitsets for c)
		boost::dynamic_bitset<unsigned char> bsCopy(bs1);
		boost::dynamic_bitset<unsigned char> bsSub(bs1);
		bsSub.flip();
		//check if it is subset
		std::cout << "are the followings the subset of bs1?\n";
		std::cout << "bsCopy: " << std::boolalpha << bsCopy.is_subset_of(bs1) << std::endl;
		std::cout << "bsSub: " << std::boolalpha << bsSub.is_subset_of(bs1) << std::endl;
		//check if it is proper subset
		std::cout << "are the followings the proper subset of bs1?\n";
		std::cout << "bsCopy: " << std::boolalpha << bsCopy.is_proper_subset_of(bs1) << std::endl;
		std::cout << "bsSub: " << std::boolalpha << bsSub.is_proper_subset_of(bs1) << std::endl;
	//end of c)
    
	//d)
	   //apply find_first for bs1
		std::cout << "find_first in bs1: " << bs1.find_first() << std::endl;
		//apply find_next in bs1
		std::cout << "find_next in bs1: " << bs1.find_next(bs1.find_first()) << std::endl;
	//end of d)
	return 0;
}