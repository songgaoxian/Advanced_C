#ifndef BitMap_H
#define BitMap_H
#include<bitset>
#include<array>
#include<functional>
template<typename V, int NR, int NC>
using NestedMatrix = std::array<std::array<V, NC>, NR>;

//copied from 3.6.1
class Proposition {
	//a class representing true/false
private:
	std::bitset<1> data;
public:
	//a)default constructor
	Proposition() { data[0] = 0; }
	//bool as argument
	Proposition(bool src) { data[0] = (int)src; }
	//std::bitset<1> as argument
	Proposition(std::bitset<1> src) : data(src) {}
	//destructor
	~Proposition() {}
	//give data info
	bool Getdata() const { return data[0]; }

	//b)
	//equality
	Proposition operator==(const Proposition& src) const {
		return Proposition(data[0] == src.data[0]);
	}
	//inequality
	Proposition operator!=(const Proposition& src) const {
		return Proposition(data[0] != src.data[0]);
	}
	//and
	Proposition operator&(const Proposition& src) const {
		return Proposition(data[0] & src.data[0]);
	}
	//or
	Proposition operator|(const Proposition& src) const {
		return Proposition(data[0] | src.data[0]);
	}
	//XOR
	Proposition operator^(const Proposition& src) const {
		return Proposition(data[0] ^ src.data[0]);
	}
	//negation
	Proposition operator!() const {
		return Proposition(!data[0]);
	}
	//assignment
	Proposition assign(bool src) const {
		return Proposition(src = data[0]);
	}
	//conditional
	friend Proposition operator%(const Proposition& A,const Proposition& B) {
		//get the bool result of A->B
		if (A.data[0] == 1 && B.data[0] == 0)
			return Proposition(false);
		else
			return Proposition(true);
	}
	//biconditional
	friend Proposition bicondition(const Proposition& A, const Proposition& B) {
		return (A%B)&(B%A);
	}
};
//copied from 3.6.3
template<typename T, int NR, int NC>
class Matrix {
private:
	NestedMatrix<T, NR, NC> m_matrix;
public:
	//default constructor
	Matrix() {}
	//constructor with val
	Matrix(T val) {
		for (int i = 0; i < NR; ++i)
			for (int j = 0; j < NC; ++j)
				m_matrix[i][j] = val;
	}
	//copy constructor
	Matrix(Matrix& m) :m_matrix(m.m_matrix) {}

	//assignment operator
	Matrix& operator=(const Matrix& src) {
		for (int i = 0; i < NR; ++i)
			for (int j = 0; j < NC; ++j)
				m_matrix[i][j] = src.m_matrix[i][j];
		return *this;
	}

	//access element 
	T& operator()(int i,int j) {
		return m_matrix[i][j];
	}
	//access element
	T operator()(int i, int j) const {
		return m_matrix[i][j];
	}

	//add
	Matrix operator+(const Matrix& src) {
		for (int i = 0; i < NR; ++i)
			for (int j = 0; j < NC; ++j)
				m_matrix[i][j] += src.m_matrix[i][j];
		return *this;
	}
	//subtract
	Matrix operator-(const Matrix& src) {
		for (int i = 0; i < NR; ++i)
			for (int j = 0; j < NC; ++j)
				m_matrix[i][j] -= src.m_matrix[i][j];
		return *this;
	}
	//unary minus
	Matrix operator-() {
		for (int i = 0; i < NR; ++i)
			for (int j = 0; j < NC; ++j)
				m_matrix[i][j] = -m_matrix[i][j];
		return *this;
	}

	//multiply
	Matrix operator*(T& val) {
		for (int i = 0; i < NR; ++i)
			for (int j = 0; j < NC; ++j)
				m_matrix[i][j] *= val;
		return *this;
	}
	//scalar multiply
	template<typename Type, int NR, int NC, typename F>
	Matrix<Type, NR, NC> friend operator*(const F& a, const Matrix<Type, NR, NC>& pt);

	//e)create modify function
	void modify(const std::function<T(T&)>& f) {
		for (int i = 0; i < NR; ++i) {
			std::array<T, NC> temp = m_matrix[i];
			//store the transformed result 
			std::array<T, NC> tempresult;
			std::transform(temp.begin(), temp.end(), tempresult.begin(), f);
			//modify m_matrix[i]
			m_matrix[i] = tempresult;
		}

	}

};
//d)implement scalar multiply
template<typename Type, int NR, int NC, typename F>
Matrix<Type, NR, NC> operator*(const F& a, const Matrix<Type, NR, NC>& pt) {
	Type convert = (Type)a;
	Matrix<Type, NR, NC> result;
	for (int i = 0; i < NR; ++i)
		for (int j = 0; j < NC; ++j)
			result.m_matrix[i][j] = convert*pt.m_matrix[i][j];
	return result;
}


#endif
