//Stock.hpp
//
//the stock class simulate one path of brownion motion
//written on 2016/7/14

#ifndef Stock_HPP
#define Stock_HPP

class Stock {
private:
	double s;//current stock price
	double mu;//current drift
	double sigma;//current volatility
	double dt;//time increment
	double z;//normal random variable
	double t;//current time
	double k;//strike price
	double expire;//expire time
public:
	Stock();//default constructor to initialise
	Stock(const Stock& stk);//copy constructor
	
	//getters
	double S() const;//return price
	double T() const;//return current time
	double MU() const;//return current drift
	double Sig() const;//return current volatility
	double K() const;//return strike price
	double Expire() const;//return expire time
	
	//modify member data
	void advance();
	
};



#endif