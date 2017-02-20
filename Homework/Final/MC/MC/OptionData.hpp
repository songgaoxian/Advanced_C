//provide initial option data

#ifndef OptionData_HPP
#define OptionData_HPP

#include<functional>
#include<tuple>

using Payoff = std::function<double(double)>;//payoff for put or call option
using Discount = std::function<double()>; //discount function

struct OptionData {
	double R; //drift
	double V;//volatility
	double Div;//dividend
	double IC;//initial condition of underlying asset
	double T;//time to maturity
	double K;//strike price
	char type;//type=='c', it is call; otherwise, put
	Payoff Pay;//payoff function at maturity
	Discount Disc; //discount function
	OptionData(std::tuple<double, double, double, double, double, double, char>& src); //constructor
	void OptionInfo();
};



#endif