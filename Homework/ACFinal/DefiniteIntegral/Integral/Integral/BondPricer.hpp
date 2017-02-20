//create bond pricer classes

#ifndef BondPricer_HPP
#define BondPricer_HPP

#include<vector>
#include"Rule.hpp"

class BondPricer {
private:
	std::vector<double> cash_flow;
	std::vector<double> time_points;
	Simpson simp;
public:
	BondPricer(std::vector<double>& cf, std::vector<double>& tp,Simpson& sp) :cash_flow(cf), time_points(tp), simp(sp) {}
	double ZeroRate(double t) { return t / 100; }
	double P_ZeroRate();
	double P_InstRate();
	double P_Yield(double y);
	double Duration(double y);
	double Convexity(double y);
};



#endif