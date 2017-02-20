#include<tuple>
#include<utility>
#include<iostream>
#include<complex>
#include<utility>
using namespace std;

template<typename T, typename Tuple, size_t N>
struct Calculator {
 template<size_t I=0>
 static inline typename enable_if<I==N,T>::type
	 sum(Tuple& t, T result) {
	 return result;
 }

 template<size_t I=0>
 static inline typename enable_if<I<N,T>::type
	 sum(Tuple& t, T result) {
	 result = result + get<I>(t);
	 return sum<I + 1>(t, result);
 }

 static inline T average(Tuple& t,T startval) {
	 T sumresult = sum(t, startval);
     return (T)(sumresult / N);
 }

 static inline T complexAve(Tuple& t, T startval) {
	 T sumresult = sum(t, startval);
	 T ave(real(sumresult) / N, imag(sumresult) / N);
	 return ave;
 }

 template<size_t I=0>
 static inline typename enable_if<I==N,T>::type
	 getmax(Tuple& t, T result) {
	 return result;
 }

 template<size_t I=0>
 static inline typename enable_if<I<N,T>::type
	 getmax(Tuple& t, T result) {
	 if (get<I>(t) > result)
		 result = get<I>(t);
	 return getmax<I + 1>(t, result);
 }

};

int main() {
	using T2D = tuple<double, double>;
	using T3D = tuple<double, double, double>;
	T2D t2 = make_tuple(3.5, 4.9);
	T3D t3 = make_tuple(5.5, 8.9, 3.3);
	double result = Calculator<double, T2D, 2>::sum(t2, 0.0);
	cout << "Sum double tuples:" << endl;
	cout << result << endl;
	double result2 = Calculator<double, T3D, 3>::sum(t3, 0.0);
	cout << result2 << endl;
	cout << "Average double tuples: " << endl;
	result = Calculator<double, T2D, 2>::average(t2,0.0);
	result2 = Calculator<double, T3D, 3>::average(t3,0.0);
	cout << result << endl;
	cout << result2 << endl;
	cout << "Max double tuples: " << endl;
	result = Calculator<double, T2D, 2>::getmax(t2, get<0>(t2));
	result2 = Calculator<double, T3D, 3>::getmax(t3, get<0>(t3));
	cout << result << endl;
	cout << result2 << endl;

	using cInt = complex<int>;
	using T3C = tuple<cInt, cInt, cInt>;
	cInt c1 = { 1,2 };
	cInt c2 = { 2,5 };
	cInt c3 = { 3,11 };
	cInt c0 = { 0,0 };
	T3C tc = make_tuple(c1, c2, c3);
	cInt sumresult = Calculator<cInt, T3C, 3>::sum(tc, c0);
	cInt averageresult = Calculator<cInt, T3C, 3>::complexAve(tc, c0);
	cout << "Sum and average for complex: \n";
	cout << sumresult << endl;
	cout << averageresult << endl;
	
	return 0;
}
