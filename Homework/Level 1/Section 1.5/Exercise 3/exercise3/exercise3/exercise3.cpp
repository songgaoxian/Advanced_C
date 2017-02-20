#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<vector>
#include<iterator>
#include<iostream>
#include<tuple>
#include<cmath>
#include<algorithm>
template<typename Container, typename T>
std::tuple<T, T, T, T, T> vectorStat(Container& input) {
	T mean = 0;
	T size = (T)input.size();
	for (unsigned int i = 0; i < input.size(); i++)
		mean += input[i] / size;
	T meanDeviation = 0;
	for (unsigned int j = 0; j < input.size(); j++) {
		meanDeviation += std::abs(input[j] - mean) / size;
	}
	T max = input[0];
	T min = input[0];
	for (unsigned int j = 0; j < input.size(); j++) {
		if (max < input[j])
			max = input[j];
		if (min > input[j])
			min = input[j];
	}
	T range = max - min;
	T var = 0;
	for (unsigned int j = 0; j < input.size(); j++) {
		var += (input[j] - mean)*(input[j] - mean) / size;
	}
	T stdev = sqrt(var);
	std::tuple<T, T, T, T, T> result = std::make_tuple(mean, meanDeviation, range, stdev, var);
	return result;
}

template<typename Container,typename T>
std::tuple<T,T> MedianMode(Container& input) {
	std::size_t N = input.size();
	std::sort(input.begin(), input.end(), [](T first, T second) { return (first < second); });
	T median;
	if (N % 2 == 1)
		median = input[(N - 1) / 2];
	else
		median = 0.5*(input[N / 2] + input[N / 2 - 1]);
	int frequency = 1;
	int maxfrequency = 1;
	T mode = input[0];
	for (unsigned int i = 1; i < input.size(); i++) {
		if (input[i] == input[i - 1]) {
			frequency++;
		}
		else {
			frequency = 1;
		}
		if (frequency > maxfrequency) {
			maxfrequency = frequency;
			mode = input[i];
		}
	}
	std::tuple<T, T> result = std::make_tuple(median, mode);
	return result;
}

int main() {
	std::vector<double> vc1 = { 1.1,4.4,6.5,7.9,8.8 };
	boost::numeric::ublas::vector<double> vc2(3);
	vc2[0] = 1.2;
	vc2[1] = 3.4;
	vc2[2] = 5.5;
	using Tup = std::tuple<double, double, double, double, double>;
	Tup tc1 = vectorStat<std::vector<double>,double>(vc1);
	Tup tc2 = vectorStat<boost::numeric::ublas::vector<double>, double>(vc2);
	double mean, range, stdev;
	std::tie(mean, std::ignore, range, stdev, std::ignore) = tc1;
	std::cout << "vector 1's mean, range and standard deviation: " << mean << ", " << range << ", " << stdev << std::endl;
	double meanDeviation, var;
	std::tie(std::ignore, meanDeviation, std::ignore, std::ignore, var) = tc2;
	std::cout << "vector 2's mean deviation and variance: " << meanDeviation << ", " << var << std::endl;
	std::vector<double> vc3 = {1.9, 2.2,1.2,2.2,2.2,1.2,3.6 };
	boost::numeric::ublas::vector<double> vc4(4);
	vc4[0] = 2.1;
	vc4[1] = 2.1;
	vc4[2] = 3.0;
	vc4[3] = 1.1;
	double median, mode;
	std::tie(median, mode) = MedianMode<std::vector<double>, double>(vc3);
	std::cout << "Vector 3's median and mode: " << median << ", " << mode << std::endl;
	std::tie(median, mode) = MedianMode<boost::numeric::ublas::vector<double>, double>(vc4);
	std::cout << "Vector 4's median and mode: " << median << ", " << mode << std::endl;
	return 0;

}