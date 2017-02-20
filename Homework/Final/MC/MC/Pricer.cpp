//Pricer.cpp
//implement methods in Pricer.hpp

#include"Pricer.hpp"
//base class
Pricer::Pricer(OptionData& src):option(src),NSim(0){}
//end

//EuropeanPricer class
EuropeanPricer::EuropeanPricer(OptionData& src):Pricer(src), price(0.0), sum(0.0) {}
void EuropeanPricer::ProcessPath(std::vector<double>& arr) {
	sum += option.Pay(arr[arr.size() - 1]);
	NSim++;
}
double EuropeanPricer::DiscountFactor() { return option.Disc(); }
void EuropeanPricer::PostProcess(int count) {
	price = DiscountFactor()*(sum/(double)NSim);
	std::cout << "\n"<<count<<" finished!\n";
}
double EuropeanPricer::Price() { return price; }
void EuropeanPricer::Summary() {
	std::cout << "\n------Summary of European Option Pricing------\n";
	option.OptionInfo();
	std::cout << "Price is " << price << " with simulation " << NSim << " times\n";
}
//end

//BarrierPricer class
BarrierPricer::BarrierPricer(OptionData& src, double b,bool stat) :Pricer(src), price(0.0), sum(0.0), barrier(b),status(stat){}
void BarrierPricer::ProcessPath(std::vector<double>& arr) {
	auto result = std::minmax_element(arr.begin(), arr.end());
	//get min and max elements of arr
	double min = *result.first;
	double max = *result.second;
	//check is the variable that can reflect if the path specified by arr has ever crossed the barrier
	double check = (min - barrier)*(max - barrier);
	//if check is greater than 0, then the path never crosses the barrier; otherwise, path crosses the barrier
	if (check <= 0) {
		//in the case that the path crosses the barrier, the status need to be changed
		if (status == true) {
			status = false;
		}
		else {
			status = true;
		}
	}
	//if status true, payoff can be nonnegative; otherwise, payoff is 0
	if (status == true) {
		sum += option.Pay(arr[arr.size() - 1]);
	}
	NSim++;
}
double BarrierPricer::DiscountFactor() { return option.Disc(); }
void BarrierPricer::PostProcess(int count) {
	price = DiscountFactor()*(sum/(double)NSim);
	std::cout << "\n" << count << " finished!\n";
}
double BarrierPricer::Price() { return price; }
void BarrierPricer::Summary() {
	std::cout << "\n------Summary of Barrier Option Pricing------\n";
	option.OptionInfo();
	std::cout << "Price is " << price << " with simulation " << NSim << " times\n";
}
//end

//class AssianPricer
AssianPricer::AssianPricer(OptionData& src) :Pricer(src), price(0.0), sum(0.0) {}
void AssianPricer::ProcessPath(std::vector<double>& arr) {
	double averagePath = std::accumulate(arr.begin(), arr.end(), 0.0) / (double)arr.size();
	sum += option.Pay(averagePath);
	NSim++;
}
double AssianPricer::DiscountFactor() { return option.Disc(); }
void AssianPricer::PostProcess(int count) {
	price = DiscountFactor()*(sum/(double)NSim);
	std::cout << "\n" << count << " finished!\n";
}
double AssianPricer::Price() { return price; }
void AssianPricer::Summary() {
	std::cout << "\n------Summary of Assian Option Pricing------\n";
	option.OptionInfo();
	std::cout << "Price is " << price << " with simulation " << NSim << " times\n";
}
//end