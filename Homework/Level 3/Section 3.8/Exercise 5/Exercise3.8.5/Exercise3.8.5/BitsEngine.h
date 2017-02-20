#ifndef BitsEngine_H
#define BitsEngine_H
#include<bitset>
#include<iostream>
#include<chrono>
#include<random>

template<class Engine, std::size_t W, class UIntType>
class independent_bits_engine {
private:
	Engine eng;
	std::bitset<W> bset;
public:
	//constructor with seed
	independent_bits_engine(UIntType seed) {
		eng.seed(seed);
	}
	UIntType operator()() {
		//generate random numbers
		UIntType result = eng();
		bset = result;
		//return the random number
		return result;
	}
	std::bitset<W>& BitSet() {
		return bset;
	}
};


#endif
