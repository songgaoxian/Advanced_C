//implement bootstrapping to calculate zero rates

#ifndef Bootstrap_HPP
#define Bootstrap_HPP

#include<vector>

class Bootstrap {
private:
	std::vector<double> cash_flow;
	std::vector<double> time_points;
	std::vector<double> knownrates;
	double price;
public:
	Bootstrap(std::vector<double>& cf,std::vector<double>& tp,std::vector<double>& kr,double p):cash_flow(cf),time_points(tp),knownrates(kr),price(p){}
	double GetZero() {
		double sum = 0;
		double r;
		int n = cash_flow.size();
		if (knownrates.size() > 0) {
			for (int i = 1; i <= n - 1; ++i) {
				sum += cash_flow[i - 1] * exp(-knownrates[i - 1] * time_points[i - 1]);
			}
		}
		r = (log(cash_flow[n - 1] / (price - sum))) / time_points[n - 1];
		knownrates.push_back(r);	
		return r;
	}
	std::vector<double> CF() const { return cash_flow; }
	void CF(std::vector<double>& cf) { cash_flow = cf; }
	
	std::vector<double> TP() const { return time_points; }
	void TP(std::vector<double>& tp) { time_points = tp; }
	
	std::vector<double> Rate() const { return knownrates; }
	
	double P() const { return price; }
	void P(double p) { price = p; }
};


#endif