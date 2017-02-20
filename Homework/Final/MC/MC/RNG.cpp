//RNG.cpp
//implement methods of classes in RNG.hpp

#include"RNG.hpp"

//class LibRandom
LibRandom::LibRandom(RngDelegate src):Rng(), randnorm(src){}
std::tuple<double, double> LibRandom::GenerateRn() {
	//std::random_device rd;
	//std::mt19937 generator(rd());
	//std::normal_distribution<double> dist(0, 1);
	//use delegate instead
	double norm = randnorm(0,1);
	double norm2 = randnorm(0,1);
	//create result tuple
	std::tuple<double, double> result(norm, norm2);
	return result;
}
//end
//class PolarMarsaglia
PolarMarsaglia::PolarMarsaglia(RngDelegate src):Rng(),randu(src){}
std::tuple<double, double> PolarMarsaglia::GenerateRn() {
	double u, v, S;
	do {
		//generate independent random variables
		u = 2.0*randu(0, 1) - 1.0;
		v = 2.0*randu(0, 1) - 1.0;
		S = u*u + v*v;
	} while (S >= 1.0);

	double fac = std::sqrt(-2.0*std::log(S) / S);
	//get two normal variables
	double norm1 = fac*u;
	double norm2 = fac*v;
	std::tuple<double, double> result(norm1, norm2);
	return result;
}
//end
//class BoxMuller
BoxMuller::BoxMuller(RngDelegate src):Rng(),randu(src){}
std::tuple<double,double> BoxMuller::GenerateRn() {
	//generate independent uniform random variables
	double u1 = randu(0, 1); 
	double u2 = randu(0, 1);
	//get two normal variables
	double norm1 = std::sqrt(-2.0*std::log(u1))*std::cos(2.0*Pi*u2);
	double norm2 = std::sqrt(-2.0*std::log(u1))*std::sin(2.0*Pi*u2);
	std::tuple<double, double> result(norm1, norm2);
	return result;
}