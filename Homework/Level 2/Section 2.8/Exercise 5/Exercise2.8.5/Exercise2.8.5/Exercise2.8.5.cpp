#include"BitMatrix.h"
int main() {
	//set N and M for BitMatrix
	const std::size_t N = 2;
	const std::size_t M = 3;
	//create an array
	std::array<std::bitset<M>, N> bs1{ std::bitset<M>(std::string("100")),std::bitset<M>(std::string("100")) };
	//create BitMatrix with the above array
	BitMatrix<std::string, N, M> bm1(bs1);
	//test some functionality
	std::cout << bm1[1][1] << std::endl; //0
	std::cout <<std::boolalpha<<bm1.any(1) << std::endl; //true
	std::cout << std::boolalpha << bm1.all() << std::endl; //false

	BitMatrix<std::string, N, M> bm2; //use default constructor
	bm2.set();
	std::cout << bm2[1][1] << std::endl; //true
	std::cout << std::boolalpha << bm2.all() << std::endl; //true

	bm2.reset();
	BitMatrix<std::string, N, M> bm3 = (bm1 & bm2);
	std::cout << bm3[1][1] << std::endl; //false
	std::cout << std::boolalpha << bm3.none(1) << std::endl; //true

	
	
	return 0;
}