#include "BitMap.h"
#include<iostream>
#include<string>
//copied
using value_type = Proposition;
template<int NR, int NC>
using BitMap = Matrix<value_type, NR, NC>;

template<int NR, int NC>
using BitMap2 = std::array<std::bitset<NC>, NR>;
 
//a)print function for BitMap
template<int NR, int NC>
void print(BitMap<NR, NC>& bit) {
	for (int i = 0; i < NR; ++i) {
		std::cout << std::endl;
		for (int j = 0; j < NC; ++j) {
			std::cout << std::boolalpha << bit(i,j).Getdata() << " ";
		}	
	}
	std::cout << std::endl;
}
//print function for BitMap2
template<int NR, int NC>
void print2(const BitMap2<NR, NC>& bit) {
	for (int i = 0; i < NR; ++i) {
		std::cout << std::endl;
		for (int j = 0; j < NC; ++j)
			std::cout << std::boolalpha << bit[i][j] << " ";
	}
	std::cout << std::endl;
}

//b)
using BitFunction = std::function<Proposition(const Proposition&,const Proposition&)>;
//free function to merge two bitmaps
template<int NR, int NC>
BitMap<NR, NC> mask(const BitMap<NR, NC>& bm1,const BitMap<NR, NC>& bm2, const BitFunction& masker) {
	BitMap<NR, NC> result;
	//apply masker to merge bm1 and bm2 and store result of merging in result
	for(int i=0; i<NR;++i)
		for (int j = 0; j < NC; ++j) {
			result(i, j) = masker(bm1(i,j), bm2(i,j));
		}
	return result;
}
//c)
template<int NR, int NC>
void initialise(BitMap2<NR, NC>& b, int row, std::string& s) {
	b[row] = std::bitset<NC>(s);
}

int main() {
	value_type p1(true);
	value_type p2(false);
	//a)
	//dimentions for bitmap
	const int NR = 3, NC = 4;
	//create an instance of BitMap
	BitMap<NR, NC> bm1(p1);
	//create a bitset
	std::bitset<NC> bs(std::string("0011"));
	//create an instance of BitMap2
	BitMap2<NR, NC> bm2;
	for (int i = 0; i < NR; ++i)
		bm2[i] = bs;
	//print out
	print<NR, NC>(bm1);
	print2<NR, NC>(bm2);

	//b)testing
	BitMap<NR, NC> b(true);
	b(1, 2) = false;
	std::cout << "b:";
	print<NR, NC>(b);

	BitMap<NR, NC> b2(false);
	b2(2, 1) = true;
	std::cout << "b2:";
	print<NR, NC>(b2);

	//the following are potential maskers
	auto Equal = [](const Proposition& p1, const Proposition& p2) {return p1 == p2; };
	auto InEqual = [](const Proposition& p1, const Proposition& p2) {return p1 != p2; };
	auto AND = [](const Proposition& p1, const Proposition& p2) {return p1&p2; };
	auto OR = [](const Proposition& p1, const Proposition& p2) {return p1 | p2; };
	auto XOR = [](const Proposition& p1, const Proposition& p2) {return p1^p2; };
	auto COND = [](const Proposition& p1, const Proposition& p2) {return p1%p2; };
	auto BICOND = [](const Proposition& p1, const Proposition& p2) {return bicondition(p1, p2); };
	//apply equal
	std::cout << "Equal";
	auto bmResult = mask(b, b2, Equal);
	print<NR, NC>(bmResult);
	//apply inequal
	std::cout << "Inequal";
	bmResult = mask(b, b2, InEqual);
	print<NR, NC>(bmResult);
	//apply AND
	std::cout << "AND";
	bmResult = mask(b, b2, AND);
	print<NR, NC>(bmResult);
	//apply OR
	std::cout << "OR";
	bmResult = mask(b, b2, OR);
	print<NR, NC>(bmResult);
	//apply XOR
	std::cout << "XOR";
	bmResult = mask(b, b2, XOR);
	print<NR, NC>(bmResult);
	//apply COND
	std::cout << "COND";
	bmResult = mask(b, b2, COND);
	print<NR, NC>(bmResult);
	//apply BICOND
	std::cout << "BICOND";
	bmResult = mask(b, b2, BICOND);
	print<NR, NC>(bmResult);

	//c)
	//create two instances of BitMap and BitMap2
	const int P = 4, Q = 8;
	BitMap<P, Q> bitblt(false);
	//assume first four elements of every row is true
	for(int i=0;i<P;++i)
	   bitblt(i, 0) = bitblt(i, 1) = bitblt(i, 2) = bitblt(i, 3) = true;
	//it takes 16 basic operations
	//if the pattern is not fixed, it will be more tedious to set each row
	print(bitblt);

	BitMap2<P, Q> bitblt2;
	initialise(bitblt2, 0, std::string("11110000"));
	initialise(bitblt2, 1, std::string("00111100"));
	initialise(bitblt2, 2, std::string("10010011"));
	initialise(bitblt2, 3, std::string("01011010"));
	//it is easy to set every row with any pattern
	print2(bitblt2);




	return 0;
}