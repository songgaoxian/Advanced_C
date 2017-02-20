//implement Rule.hpp

#include"Rule.hpp"

double Rule::GetIntegral() {
	std::cout.precision(13);
	int n = Size();
	double h = GetH();
	double integral = 0.0;
	double startVal = Start() + 0.5*h;
	for (int i = 0; i < n; ++i) {
		integral += oneStep(startVal);
		startVal += h;
	}
	std::cout << "n=" << n << ";integral=" << std::exp(-integral) << "\n";
	//get initial integral result
	double result;
	double diff;
	int count = 1;
	//loop until result is satisfied with thresh
	do {
		result = 0.0;
		n *= 2;
		Size(n);
		h = GetH();
		startVal = Start() + 0.5*h;
		for (int i = 0; i < n; ++i) {
			result += oneStep(startVal);
			startVal += h;
		}
		diff = std::abs(result - integral);
		integral = result;
		std::cout << "n=" << n << ";integral=" << std::exp(-integral) << '\n';
		count++;
	} while (diff >= thresh);
	std::cout << "It takes " << count << " times\n";
	
	return integral;
}

double MidPoint::oneStep(double x) {
	double h = GetH();
	return h*f(x);
}

double Simpson::oneStep(double x) {
	double h = GetH();
	return h / 6.0*(f(x - 0.5*h) + 4.0*f(x) + f(x + 0.5*h));
}