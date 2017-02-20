//implement classes in Newton.hpp

#ifndef Newton_CPP
#define Newton_CPP
#include"Newton.hpp"

template<typename Instrument>
double Newton<Instrument>::compute(double x0, double price, Instrument c) {
	std::tuple<double, double> result;
	double f, df;
	do {
		result = f_inst(x0, price, c);
		f = std::get<0>(result);
		df = std::get<1>(result);
		x0 = x0 - f / df;
	} while (f >= thresh);
	return x0;
}
#endif
