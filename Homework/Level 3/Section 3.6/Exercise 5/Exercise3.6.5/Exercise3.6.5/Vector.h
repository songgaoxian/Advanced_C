//copied from 3.6.2
#ifndef VectorMatrix_H
#define VectorMatrix_H
#include<array>
#include<functional>
#include<iterator>
#include<xutility>
//a)
template<typename T, int N> class Vector;

template<typename T, int N>
class Vector {
private:
	std::array<T, N> arr;
public:
	//default constructor
	Vector() {}
	//constructor with val
	Vector(T val) {
		for (auto it = arr.begin(); it != arr.end(); it++)
			*it = val;
	}
	//copy constructor
	Vector(const Vector& vc) :arr(vc.arr) {}
	//assignment operator
	Vector& operator=(const Vector& vc) {
		arr = vc.arr;
		return *this;
	}


	//access elements with []
	T& operator[](int i) {
		return arr[i];
	}
	//access element
	T operator[](int i) const {
		return arr[i];
	}
	//c)
	//add
	Vector operator+(const Vector& src) {
		for (int i = 0; i < N; ++i)
			arr[i] += src.arr[i];
		return *this;
	}
	//subtract
	Vector operator-(const Vector& src) {
		for (int i = 0; i < N; ++i)
			arr[i] = arr[i] - src.arr[i];
		return *this;
	}
	//unary minus
	Vector operator-() {
		for (int i = 0; i < N; ++i)
			arr[i] = -arr[i];
		return *this;
	}
	//multiply
	Vector operator*(T val) {
		for (int i = 0; i < N; ++i)
			arr[i] *= val;
		return *this;
	}
	//declare scalar multiply
	template<typename Type, int N, typename F>
	Vector<Type, N> friend operator*(const F& a, const Vector<Type, N>& pt);
	//e)modify
	void modify(const std::function<T(T&)>& f) {
		std::array<T, N> result;
		//store transformed arr value in result
		std::transform(arr.begin(), arr.end(), result.begin(), f);
		arr = result;
	}

	//a)give specified iterator
	std::_Array_const_iterator<T,N> It(int index) const {
		return arr.begin()+index;
	}

};
//d)scalar multiply
template<typename Type, int N, typename F>
Vector<Type, N> operator*(const F& a, const Vector<Type, N>& pt) {
	Type ta = (Type)a;
	Vector<Type, N> result;
	for (int i = 0; i < N; ++i)
		result[i] = ta*pt.arr[i];
	return result;
}

#endif

