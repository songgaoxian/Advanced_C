//RNG.hpp
//create different classes to use various ways to get normal random variables

#ifndef RNG_HPP
#define RNG_HPP

#define Pi 3.14159265

#include<random>
#include<tuple>
#include<functional>

//declare delegate
using RngDelegate = std::function<double(double,double)>;

//create function to generate random variable following standard normal or u(0,1)
template<typename Distribution>
double Rand(double para1,double para2) {
	std::random_device rd;
	std::mt19937 gen(rd());
	Distribution dist(para1, para2); //specify the distribution
	return dist(gen); //return generated random variable
}


//the class acts as interface
class Rng {
public:
	virtual std::tuple<double,double> GenerateRn() = 0;
};

//directly use random lib
class LibRandom :public Rng {
private:
	RngDelegate randnorm;
public:
	LibRandom(RngDelegate src);
	std::tuple<double, double> GenerateRn();
};

//use Polar Marsaglia 
class PolarMarsaglia :public Rng {
private:
	RngDelegate randu;
public:
	PolarMarsaglia(RngDelegate src);
	std::tuple<double, double> GenerateRn();
};

//use Box-Muller
class BoxMuller : public Rng {
private:
	RngDelegate randu;
public:
	BoxMuller(RngDelegate src);
	std::tuple<double, double> GenerateRn();
};



#endif