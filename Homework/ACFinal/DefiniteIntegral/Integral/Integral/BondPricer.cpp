//implement BondPricer
#include"BondPricer.hpp"

double BondPricer::P_ZeroRate() {
	double price = 0;
	for(int i=0;i<cash_flow.size();++i){
		price += cash_flow[i] * std::exp(-ZeroRate(time_points[i])*time_points[i]);
	}
	return price;
}
double BondPricer::P_InstRate() {
	double price = 0;
	for (int i = 0; i < cash_flow.size(); ++i) {
		simp.End(time_points[i]);
		simp.Start(0);
		price += cash_flow[i] * std::exp(-simp.GetIntegral());
	}
	return price;
}
double BondPricer::P_Yield(double y) {
	double price = 0;
	double interval = time_points[1] - time_points[0];
	for (int i = 0; i < cash_flow.size(); ++i) {
		price += cash_flow[i] / std::pow((1 + y*interval), time_points[i]/interval);
	}
	return price;
}
double BondPricer::Duration(double y){
	double h = 10E-5;
	double price = P_Yield(y);
	double derivative = (P_Yield(y + 0.5*h) - P_Yield(y - 0.5*h)) / h;
	return -derivative / price;
}
double BondPricer::Convexity(double y) {
	double h = 10E-5;
	double price = P_Yield(y);
	double derivative2 = (P_Yield(y + h) + P_Yield(y - h) - 2 * price) / (h*h);
	return derivative2 / price;
}