//test codes

#include"Rule.hpp"
#include"BondPricer.hpp"
#include"BS.hpp"
#include"Newton.hpp"
#include"Bootstrap.hpp"

Func<Call> f_call = [](double x, double price, Call c)->std::tuple<double, double> {
	c.Sigma(x);
	double f = c.Price() - price;
	double df = c.Vega();
	std::tuple<double, double> result(f, df);
	return result;
};

Func<BondPricer> f_bond = [](double x, double price, BondPricer bp)->std::tuple<double, double> {
	double f = bp.P_Yield(x) - price;
	double h = 10E-5;
	double df = (bp.P_Yield(x + h) - bp.P_Yield(x - h)) / (2.0*h);
	std::tuple<double, double> result(f, df);
	return result;
};

int main() {
	//declare variables to use in midpoint and simpson rule
	/*double start=0, end=3.0/12.0, thresh=10E-12;
	int size = 4;
	Simpson simp(start, end, size, thresh);
	Call c(10, 10, 0.0, 0, 0.4, 1, simp);
	std::cout << "Price=" << c.Price() << " Delta=" << c.Delta() << " Vega=" << c.Vega() << '\n';
	
	thresh = 10E-4;
	Newton<Call> nt(thresh, f_call);
	std::cout<<"Implied volatility="<<nt.compute(0.2, c.Price(), c)<<"\n(Exact=0.4)\n";*/

	std::vector<double> cf1 = { 100 }, cf2 = { 2,102 };
	std::vector<double> tp1 = { 0.5 }, tp2 = { 0.5,1 };
	double p1 = 99, p2 = 102;
	std::vector<double> rates;
	Bootstrap bstp(cf1, tp1, rates, p1);
	//get first rate
	bstp.GetZero();
	//update data for second rate cal
	bstp.CF(cf2);
	bstp.TP(tp2);
	bstp.P(p2);
	//get second rate
	bstp.GetZero();
	rates = bstp.Rate();
	//print
	for (int i = 0; i < rates.size(); i++) {
		std::cout << "r" << i + 1 << "=" << rates[i] << '\n';
	}
	
	return 0;
}