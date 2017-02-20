//Pricer.hpp
//create classes for Pricer module

#ifndef Pricer_HPP
#define Pricer_HPP

#include<functional>
#include<vector>
#include<iostream>
#include<algorithm>
#include<numeric>
#include"OptionData.hpp"


//base class to act as an interface
class Pricer{
protected:
	OptionData option;
	long long NSim; //number of simulation
public:
	Pricer(OptionData& src);
	virtual void ProcessPath(std::vector<double>& arr)=0;
	virtual void PostProcess(int count) = 0;
	virtual double DiscountFactor() = 0;
	virtual double Price() = 0;
	virtual void Summary() = 0;//summary of the pricing
};
//European Pricer
class EuropeanPricer : public Pricer
{
private:
	double price; 
	double sum; //average of payoff
public:
	EuropeanPricer(OptionData& src);
	void ProcessPath(std::vector<double>& arr); //arr stores the path of underlying asset
	double DiscountFactor();
	void PostProcess(int count);//signal that it is finished
	void Summary();//summary of european pricing
	double Price();
};
//Barrier Pricer
class BarrierPricer :public Pricer
{
private:
	double price;
	double sum;
	bool status; //whether the option is initially valid
	double barrier; //barrier in the option
public:
	BarrierPricer(OptionData& src, double b,bool stat);
	void ProcessPath(std::vector<double>& arr);
	double DiscountFactor();
	void PostProcess(int count);//signal that it is finshed
	double Price();
	void Summary();//summary of barrier pricing
};
//Assian Pricer
class AssianPricer :public Pricer
{
private:
	double price;
	double sum;
public:
	AssianPricer(OptionData& src);
	void ProcessPath(std::vector<double>& arr);
	double DiscountFactor();
	void PostProcess(int count);//signal that it is finished
	double Price();
	void Summary();//summary of assian pricing
};


#endif