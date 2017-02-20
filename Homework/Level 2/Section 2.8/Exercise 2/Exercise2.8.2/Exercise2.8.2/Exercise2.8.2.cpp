#include<bitset>
#include<string>
#include<iostream>

int main() {
	const std::size_t N = 7;
	//a)
	//create bs1 and bs2 with same size of 7
	std::bitset<N> bs1(std::string("0010011"));
	std::bitset<N> bs2(std::string("0110110"));
	//print out bs1 and bs2
	std::cout << "a):\n" << "bs1=" << bs1 << "; bs2=" << bs2 << std::endl;
	//end of a)

	//b)
	//toggle all bits of bs1 and bs2
	bs1.flip();
	bs2.flip();
	//print out bs1 and bs2
	std::cout << "b):\n" << "bs1=" << bs1 << "; bs2=" << bs2 << std::endl;
	//end of b)

	//c)
	//perform XOR without modification
	std::bitset<N> bsXOR = bs1^bs2;
	std::cout << "c)\n" << "bsXOR=" << bsXOR << std::endl;
	//perform OR with modification
	bs1 |= bs2;
	std::cout << "after OR: bs1=" << bs1 << std::endl;
	//perform AND without modification
	std::cout << "AND on bs1 and bs2: " << (bs1 & bs2) << std::endl;
	//end of c)

	//d)
	int n = 2;//num to shift
	//shift bs1 to right without modification
	std::bitset<N> bsRight = (bs1 >> n);
	std::cout << "d)\n" << "bsRight=" << bsRight << std::endl;
	//shift bs2 to left with modification
	bs2 <<= n;
	std::cout << "after left shift, bs2=" << bs2 << std::endl;
	//end of d)

	//e)
	//create hash object
	std::hash<std::bitset<N>> bhash;
	//display hashed values
	std::cout << "hashed value for bs1: " << bhash(bs1) << std::endl;
	std::cout << "hashed value for bs2: " << bhash(bs2) << std::endl;
	//end of e)
	return 0;
}