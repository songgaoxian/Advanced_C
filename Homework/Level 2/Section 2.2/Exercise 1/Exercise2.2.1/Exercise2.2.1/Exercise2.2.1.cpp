#include<type_traits>
#include<iostream>
#include<vector>
#include<array>
#include<complex>
#include<algorithm>
using std::cout;

//a) define addition 
//this function implements Addition if the input type is compound instead of scalar
template<typename T>
T Addition_impl(const T& t1, const T& t2, std::true_type) {
	//assign t1 to result
	T result = t1;
	//add two inputs t1 and t2
	for (std::size_t i = 0; i < t1.size(); i++)
		result[i] = t2[i] + t1[i];
	return result;
}
//this function implements Addition if the input type is scalar
template<typename T>
T Addition_impl(const T& t1, const T& t2, std::false_type) {
	//just return t1+t2
	return t1 + t2;
}
//this function is Addition which calls its implementations
template<typename T>
T Addition(const T& t1, const T& t2) {
	return Addition_impl(t1, t2, std::is_compound<T>());
}
//end of a)

//b) define additive inverse
//this function implements additive inverse if input is of type compound
template<typename T>
void AdditiveInverse_impl(T& val, std::true_type) {
	//change the sign of every element of val
	for (std::size_t i = 0; i < val.size(); i++)
		val[i] = -val[i];
}
//this function implements additive inverse if input is of type scalar
template<typename T>
void AdditiveInverse_impl(T& val, std::false_type) {
	//just change the sign of the scalar val
	val = -val;
}
//this function is AdditiveInverse which calls its implementations
template<typename T>
void AdditiveInverse(T& val) {
	AdditiveInverse_impl(val, std::is_compound<T>());
}
//end of b)

//c) define scalar multiply
//assume typename Scalar is a scalar type
//this function implements scalar multipy if the input of compound type
template<typename Scalar, typename T>
T ScalarMulti_impl(const Scalar s, const T& val, std::true_type) {
	//initialize result of type T
	T result(val);
	//convert the type of Scalar s to the type consistent with elements of type T
	decltype(val[0]) appS = (decltype(val[0]))s;
	//apply scalar multiplication to get appropriate value for result
	for (std::size_t i = 0; i < val.size(); i++) {
		result[i] = val[i] * appS;
	}
	return result;
}
//this function implements scalar multiply if input is of scalar type
template<typename Scalar, typename T>
T ScalarMulti_impl(const Scalar s, const T& val, std::false_type) {
	//convert the type of Scalar s to the type consistent with type T
	T appS = (T)s;
	//just return the scalar multiplication result
	return appS*val;
}
//this function is Scalar Multiplication which calls its implementations
template<typename Scalar, typename T>
T ScalarMulti(const Scalar s, const T& val) {
	return ScalarMulti_impl(s, val, std::is_compound<T>());
}
//end of c

//print only vectors or arrays 
template<typename Container>
void print(Container& c) {
	for (auto i : c) {
		cout << i << " ";
	}
	cout << "end\n";
}

int main() {
	//d) test functions for double, array and vector
	//declare and initialize variables for testing
	double t1 = 11.2;
	double t2 = 22.3;
	int scalar = 2;
	const size_t N = 5;
	std::vector<double> vc1{ 1.1,2.2,3.3,4.4,5.5 };
	std::vector<double> vc2{ 3.0,4.0,5.0,6.0,7.5 };
	std::array<double, N> arr1{ 2.1,3.1,4.1,5.5,6.6 };
	std::array<double, N> arr2{ 0.9,0.8,0.6,4.5,6.7 };

	//test double
	cout << "test double\n";
	//print result of Addition and Scalar Multiplication
	cout << "Addition: " << Addition(t1, t2) << ";Scalar Multiply: " << ScalarMulti(scalar, t1) << "; Additive inverse: ";
	//apply Additive Inverse and print double t1
	AdditiveInverse(t1);
	cout << t1 << std::endl;

	//test vector
	cout << "test vector\n";
	//get result of Addition
	std::vector<double> result = Addition(vc1, vc2);
	cout << "Addition:\n";
	//print result of Addition
	print(result);
	//get result of Scalar Multiplication
	result = ScalarMulti(scalar, vc1);
	cout << "Scalar Multiply:\n";
	//print result of Scalar Multiplication
	print(result);
	cout << "Inverse:\n";
	//Apply Additive Inverse to vc1 and print vc1
	AdditiveInverse(vc1);
	print(vc1);

	//test array
	cout << "test array\n";
	//get result of Addition
	std::array<double, N> arr3 = Addition(arr1, arr2);
	cout << "Addition:\n";
	//print result of Addition
	print(arr3);
	//get result of Scalar Multiplication
	arr3 = ScalarMulti(scalar, arr1);
	//print result of Scalar Multiplication
	cout << "Scalar Multiply:\n";
	print(arr3);
	//Apply Additive Inverse to arr1 and print arr1
	cout << "Inverse:\n";
	AdditiveInverse(arr1);
	print(arr1);
	//end of d)

	//e) test container of complex
	cout << "test vector of complex<double>\n";
	//type complex<double> can be written as cdouble
	using cdouble = std::complex<double>;
	//declare and initialize two vectors of cdouble
	std::vector<cdouble> vcc1{ cdouble(1.2,2.1),cdouble(2.3,2.1),cdouble(3.8,1.9) };
	std::vector<cdouble> vcc2{ cdouble{ 5.0,6.2 },cdouble(7.1,7.2),cdouble(9.3,2.2) };
	//get result of Addition for vectors of cdouble
	std::vector<cdouble> cresult = Addition(vcc1, vcc2);
	cout << "Addition:\n";
	//print the result of Addition
	print(cresult);
	//get result of Scalar Multiplication
	cresult = ScalarMulti(scalar, vcc1);
	cout << "Scalar Multiply\n";
	//print the result of Scalar Multiplication
	print(cresult);
	cout << "Inverse\n";
	//Apply Additive Inverse to vcc1 and print vcc1
	AdditiveInverse(vcc1);
	print(vcc1);
	//end of e)
	return 0;
}