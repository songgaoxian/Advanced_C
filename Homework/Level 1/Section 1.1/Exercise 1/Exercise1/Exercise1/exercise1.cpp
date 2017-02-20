#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<iterator>
#include<array>
using namespace std;
//get max and min
auto f1 = [](array<double,5>& arr)->pair<double, double> {
	double max = arr[0];
	double min = arr[0];
	for (int i = 0; i <= 4; i++) {
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	pair<double, double> result;
	result = make_pair(min, max);
	return result;
};
int main() {
	double multiplier = 5.5;
	array<double, 5> inputarr;
	for (int i = 0; i <= 4; i++) inputarr[i] = (double)i*0.5;
	auto f2 = [multiplier](array<double, 5>& arr) {
		for (int i = 0; i <= 4; i++) {
			arr[i] *= multiplier;
			std::cout<< arr[i] << ", ";
		}
	}; //copy-by-value
	auto f3 = [&multiplier](array<double, 5>& arr) {
		for (int i = 0; i <= 4; i++) {
			arr[i] *= multiplier;
			std::cout << arr[i] << ", ";
		}
	}; //by reference
	std::cout<<endl;
	std::cout << "first time multiply: ";
	f2(inputarr);
	std::cout << endl;
	std::cout << "second time multiply: ";
	f3(inputarr);
	std::cout << endl;
	//a)
	std::cout << endl;
	std::cout << "Display: ";
	for (auto it = inputarr.begin(); it != inputarr.end(); it++) std::cout << *it << ", ";
	//b)
	std::cout << endl;
	array<double, 5> arr;
	arr[0] = 1.5;
	arr[1] = 3.3;
	arr[2] = 2.2;
	arr[3] = 0.9;
	arr[4] = 9.9;
	pair<double,double> minmax=f1(arr);
	std::cout << "Min and Max are " << minmax.first << ", " << minmax.second << endl;
	//c
	auto calMinMax = minmax_element(arr.begin(), arr.end());
	std::cout << "result from minmax_element's min and max are" << *calMinMax.first << ", " << *calMinMax.second << endl;
	//d
	//results are same and codes are easy to understand
	return 0;
}