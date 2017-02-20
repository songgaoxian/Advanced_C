#ifndef TMP_H
#define TMP_H
#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>
using InputFunction = std::function<double()>;
using OutputFunction = std::function<void(const std::vector<double>&)>;

class TMPClass {
private:
	InputFunction input;
	OutputFunction output;
	std::vector<double> vc;
public:
	TMPClass() {
		vc.push_back(0);
		input = []() {return 0; };
		output = [](const std::vector<double>& v) {std::cout << 0 << std::endl; };
	}
	TMPClass(std::size_t n, double startValue, InputFunction iFunction, OutputFunction oFunction) :input(iFunction), output(oFunction) {
		for (int i = 0; i < n; i++)
			vc.push_back(startValue);
	}
	void Calculate() {
		double val = input();
		std::vector<double> result;
		result.resize(vc.size());
		std::transform(vc.begin(), vc.end(), result.begin(), [=](double i) {i *= val; return i; });
		output(result);
	}
};
#endif