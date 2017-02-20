//implement BS.hpp
#include"BS.hpp"

double Call::Price() {
	double d1 = std::log(s / k) + (r - q + sigma*sigma*0.5)*t;
	d1 /= (sigma*std::sqrt(t));
	double d2 = d1 - sigma*std::sqrt(t);
	simp.Start(0);
	simp.End(d1);
	double nd1 = simp.GetIntegral() + 0.5;
	simp.End(d2);
	double nd2 = simp.GetIntegral() + 0.5;
	double price = s*std::exp(-q*t)*nd1 - k*std::exp(-r*t)*nd2;
	return price;
}
double Call::Delta() {
	double h = 10E-5;
	double originS = s;
	S(originS + h);
	double price1 = Price();
	S(originS - h);
	double price2 = Price();
	S(originS);
	return (price1 - price2) / (2.0*h);
}
double Call::Vega() {
	double h = 10E-5;
	double originS = sigma;
	Sigma(originS + h);
	double price1 = Price();
	Sigma(originS - h);
	double price2 = Price();
	Sigma(originS);
	return (price1 - price2) / (2.0*h);
}