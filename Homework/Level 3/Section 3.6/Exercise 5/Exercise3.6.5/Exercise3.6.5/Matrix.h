//copied from 3.6.3
#ifndef Matrix_H
#define Matrix_H
#include<array>
#include<functional>
template<typename V, int NR, int NC>
using NestedMatrix = std::array<std::array<V, NC>, NR>;

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
	T& operator()(int i, int j) {
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

