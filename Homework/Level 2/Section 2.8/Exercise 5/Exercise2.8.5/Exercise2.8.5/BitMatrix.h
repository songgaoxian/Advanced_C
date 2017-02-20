#ifndef BitMatrix_H
#define BitMatrix_H
#include<bitset>
#include<iostream>
#include<string>
#include<array>

template<typename T, std::size_t N, std::size_t M>
class BitMatrix {
private:
	//a) choose std::array
	std::array<std::bitset<M>, N> bitM;
	//M colums and N rows
public:
	//b)
	//default contructor and use defaults of bitset
	BitMatrix() :bitM(std::array<std::bitset<M>, N>()) {}
	//constructor
	BitMatrix(const std::array<std::bitset<M>, N>& src) :bitM(src) {}
	//copy constructor
	BitMatrix(const BitMatrix& src) :bitM(src.bitM) {}
	//assignment operator
	BitMatrix<T, N, M>& operator=(const BitMatrix& src) {
		bitM = src.bitM;
		return *this;
	}
	//destructor
	~BitMatrix() {}
	//end of b)

	//c)
	//for all rows
	//set and reset
	void set() {
		for (auto it = bitM.begin(); it != bitM.end(); ++it)
			(*it).set();
	}
	void reset() {
		for (auto it = bitM.begin(); it != bitM.end(); ++it)
			(*it).reset();
	}
	//flip
	void flip() {
		for (auto it = bitM.begin(); it != bitM.end(); ++it)
			(*it).flip();
	}
	//test none, all or any bits are set
	bool none()const {
		bool result = true;
		for (auto it = bitM.begin(); it != bitM.edn(); ++it)
			result &= (*it).none();
		return result;
	}
	bool all()const {
		bool result = true;
		for (auto it = bitM.begin(); it != bitM.end(); ++it)
			result &= (*it).all();
		return result;
	}
	bool any()const {
		bool result = false;
		for (auto it = bitM.begin(); it != bitM.end(); ++it)
			result |= (*it).any();
		return result;
	}
	//count number of set bits
	std::size_t count() const {
		std::size_t ini = 0;
		for (auto it = bitM.begin(); it != bitM.end(); ++it)
			ini += (*it).count();
		return ini;
	}

	//for a given row
	//access a given row
	//assume row index is valid
	std::bitset<M>& operator[](std::size_t row) {
		return bitM[row];
	}
	//set and reset a row
	void set(std::size_t row) {
		bitM[row].set();
	}
	void reset(std::size_t row) {
		bitM[row].reset();
	}
	//flip bits of a row
	void flip(std::size_t row) {
		bitM[row].flip();
	}
	//test if none, all or any bits are set
	bool none(std::size_t row) const {
		return bitM[row].none();
	}
	bool all(std::size_t row) const {
		return bitM[row].all();
	}
	bool any(std::size_t row) const {
		return bitM[row].any();
	}
	//count number of set bits in a row
	std::size_t count(std::size_t row) const {
		return bitM[row].count();
	}
	//end of c)

	//d)
	//create OR member function
	BitMatrix<T, N, M>& operator | (const BitMatrix<T, N, M>& src) {
		for (std::size_t i = 0; i < N; ++i) {
			bitM[i] |= src.bitM[i];
		}
		return *this;
	}
	//create XOR member function
	BitMatrix<T, N, M>& operator ^ (const BitMatrix<T, N, M>& src) {
		for (std::size_t i = 0; i < N; ++i) {
			bitM[i] ^= src.bitM[i];
		}
		return *this;
	}
	//create AND member function
	BitMatrix<T, N, M>& operator & (const BitMatrix<T, N, M>& src) {
		for (std::size_t i = 0; i < N; ++i) {
			bitM[i] &= src.bitM[i];
		}
		return *this;
	}
	//end of d)
};
#endif
