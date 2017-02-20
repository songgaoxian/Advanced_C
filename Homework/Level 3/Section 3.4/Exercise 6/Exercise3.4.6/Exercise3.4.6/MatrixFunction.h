#ifndef Matrix_H
#define Matrix_H
#include<iostream>
#include<vector>
#include<array>
#include<future>
#include<thread>
#include<chrono>
template<typename T>
class Matrix {
private:
	int rows;
	int cols;
	T val;
	T** m;
public:
	//default constructor
	Matrix() {}
	//constructor
	Matrix(int nr, int nc, T srcval) :rows(nr), cols(nc), val(srcval) {
		m = new T*[rows];
		T ini = 0;
		for (int i = 0; i < rows; ++i) {
			m[i] = new T[cols];
			for (int j = 0; j < cols; ++j) {
				m[i][j] = val + ini;
				ini += 0.2;
			}
		}
	}
	//destructor
	~Matrix() {
	}
	//get val
	T GetVal() { return val; }
	//get rows
	int GetRow() { return rows; }
	//get cols
	int GetCol() { return cols; }
	//set m's element
	void Set(int r, int c, T newval) { m[r][c] = newval; }
	//Get m's element
	T Get(int r, int c) const { return m[r][c]; }
};
template<typename T>
Matrix<T> F1Matrix(Matrix<T> a) {
	T newval = a.GetVal() * 2;
	Matrix<T> result(a.GetRow(), a.GetCol(), newval);
	for(int i=0;i<result.GetRow();i++)
		for (int j = 0; j < result.GetCol(); ++j) {
			newval = T(i + j) / 22.1 + result.Get(i, j) / (i + 11.1);
			result.Set(i, j, newval);
		}
	return result;
}
template<typename T>
Matrix<T> F2Matrix(Matrix<T> a) {
	T newval = a.GetVal() + 10;
	Matrix<T> result(a.GetRow(), a.GetCol(), newval);
	for (int i = 0; i<result.GetRow(); i++)
		for (int j = 0; j < result.GetCol(); ++j) {
			newval = T(i + j) / 27.9 + result.Get(i, j) / (j + 12.1);
			result.Set(i, j, newval);
		}
	return result;
}
template<typename T>
Matrix<T> F3Matrix(Matrix<T> c) {
	T newval = c.GetVal() / 2.1;
	Matrix<T> result(c.GetRow(), c.GetCol(), newval);
	for (int i = 0; i<result.GetRow(); i++)
		for (int j = 0; j < result.GetCol(); ++j) {
			newval = T(j) / 11.1 + result.Get(i, j) / (i + 8.1);
			result.Set(i, j, newval);
		}
	return result;
}
template<typename T>
Matrix<T> F4Matrix(Matrix<T> b, Matrix<T> d) {
	T newval = b.GetVal() + d.GetVal();
	Matrix<T> result(b.GetRow(), b.GetCol(), newval);
	for (int i = 0; i<result.GetRow(); i++)
		for (int j = 0; j < result.GetCol(); ++j) {
			newval = T(j) / 11.1 + result.Get(i, j) / (i + 4.1);
			result.Set(i, j, newval);
		}
	return result;
}
//a)Single thread implementation
template<typename T>
Matrix<T> SingleThreadMatrix(Matrix<T> a) {
	Matrix<T> b = F1Matrix<T>(a);
	Matrix<T> c = F2Matrix<T>(a);
	Matrix<T> d = F3Matrix<T>(c);
	return F4Matrix<T>(b, d);
}
//b)async and future implementation
template<typename T>
Matrix<T> asyncfutureMatrix(Matrix<T> a) {
	std::future<Matrix<T>> b = std::async(F1Matrix<T>, a);
	Matrix<T> c = F2Matrix<T>(a);
	Matrix<T> d = F3Matrix<T>(c);
	return F4Matrix<T>(b.get(), d);
}
//c) use promise
template<typename T>
void Getb(Matrix<T> a, std::promise<Matrix<T>> p) {
	Matrix<T> b = F1Matrix<T>(a);
	p.set_value(b);
}
template<typename T>
Matrix<T> promiseMatrix(Matrix<T> a) {
	std::promise<Matrix<T>> sharedData;
	std::shared_future<Matrix<T>> fut = sharedData.get_future();
	Getb<T>(a, std::move(sharedData));
	Matrix<T> c = F2Matrix<T>(a);
	Matrix<T> d = F3Matrix<T>(c);
	return F4Matrix<T>(fut.get(), d);
}
//d)use packaged task
template<typename T>
Matrix<T> packagedtaskMatrix(Matrix<T> a) {
	std::packaged_task<Matrix<T>(Matrix<T>)> task1(F1Matrix<T>);
	std::packaged_task<Matrix<T>(Matrix<T>)> task2(F2Matrix<T>);
	std::future<Matrix<T>> b = task1.get_future();
	std::future<Matrix<T>> c = task2.get_future();
	//start tasks
	task1(a);
	task2(a);
	Matrix<T> d = F3Matrix<T>(c.get());
	return F4Matrix<T>(b.get(), d);
}


#endif
