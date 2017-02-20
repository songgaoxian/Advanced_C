//use newton method to compute implied volatility

#ifndef Newton_HPP
#define Newton_HPP

#include"BS.hpp"
#include"BondPricer.hpp"
#include<functional>
#include<tuple>

template<typename Instrument>
using Func = std::function<std::tuple<double, double>(double x, double price, Instrument i)>;
 
template<typename Instrument>
class Newton {
private:
	double thresh;
	Func<Instrument> f_inst;
public:
	Newton(double thr, Func<Instrument> f) :f_inst(f), thresh(thr) {}
	double compute(double x0, double price,Instrument i);
};


#include"Newton.cpp"

#endif