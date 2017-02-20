#include<type_traits>
#include<iostream>
#include<vector>
#include<complex>
#include<array>
using std::cout;
class A {};

int main() {
	//a test is_array
	cout << "Is Array?\n";
	//test if int is an array type
	cout << "int: " << std::boolalpha << std::is_array<int>::value << std::endl;
	//test if double is an array type
	cout << "double: " << std::boolalpha << std::is_array<double>::value << std::endl;
	//test if float is an array type
	cout << "float: " << std::boolalpha << std::is_array<float>::value << std::endl;
	//test if class A is an array type
	cout << "A: " << std::boolalpha << std::is_array<A>::value << std::endl;
	//test if vector is an array type
	cout << "vector: " << std::boolalpha << std::is_array<std::vector<double>>::value << std::endl;
	//test if complex is an array type
	cout << "complex: " << std::boolalpha << std::is_array<std::complex<int>>::value << std::endl;
	//test if int[] is an array type
	cout << "int[]: " << std::boolalpha << std::is_array<int[]>::value << std::endl;
	const std::size_t N = 10;
	//test if std::array is an array type
	cout << "array: " << std::boolalpha << std::is_array<std::array<double, N>>::value << std::endl;
	//end of a)

	//b find the rank and extent of int[][3][4][5]
	//create arr as type int[][3][4][5]
	using arr = int[][3][4][5];
	cout << "arr: \n";
	//get rank of arr 
	cout << "rank: " << std::rank<arr>::value << std::endl;
	//get extent of arr at different dimensions
	cout << "extent at 0: " << std::extent<arr, 0>::value << "; extent at 1: " << std::extent<arr, 1>::value << "; extent at 2: " << std::extent<arr, 2>::value << std::endl;
	//end of b)

	//c apply remove_extent and remove_all_extents
	//remove_extent of arr gradually
	using A1 = std::remove_extent<arr>::type;
	using A2 = std::remove_extent<A1>::type;
	using A3 = std::remove_extent<A2>::type;
	using A4 = std::remove_extent<A3>::type;
	//check rank of A1 when remove_extent is called once
	cout << "A1 rank: " << std::rank<A1>::value << std::endl;
	//check rank of A2 when remove_extent is called twice
	cout << "A2 rank: " << std::rank<A2>::value << std::endl;
	//check rank of A3 when remove_extent is called three times
	cout << "A3 rank: " << std::rank<A3>::value << std::endl;
	//check rank of A4 when remove_extent is called four times
	cout << "A4 rank: " << std::rank<A4>::value << std::endl;
	//check if A4 is same as int
	cout << "is A4 same as int?" << std::boolalpha << std::is_same<int, A4>::value << std::endl;
	//call remove_all_extents on arr
	using A5 = std::remove_all_extents<arr>::type;
	//check if A5 is same as int
	cout << "is A5 same as int?" << std::boolalpha << std::is_same<int, A5>::value << std::endl;
	//end of c)
	return 0;
}