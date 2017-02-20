//Exercise4.9.4
//
//Exercise to use numeric combiner to sum up 
//returned values from slots
//written on 2016/6/23
#include"CombinerSlot.h"
#include<boost/signals2.hpp>

double Sum(double x, double y) {
	return slot1(x, y) + slot2(x, y) + slot3(x, y);
}

int main() {
	//c)create a signal
	boost::signals2::signal<double(double, double), SumCombiner<double>> sig;
	//connect slots to sig
	sig.connect(&slot1);
	sig.connect(&slot2);
	sig.connect(&slot3);
	//give two doubles
	double x = 1.2, y = 2.3;
	//emit sig
	std::cout << "Emit signal:\n";
	double result = sig(x, y);
	
	//get sum from Sum
	std::cout << "\nCall Sum:\n";
	double sum = Sum(x, y);
	//check output is correct
	if (sum == result) {
		std::cout << "\nThe output is correct with value " << sum << '\n';
	}
	else {
		std::cout << "\nThe output is incorrect as " << sum << "!=" << result << '\n';
	}

	return 0;

}