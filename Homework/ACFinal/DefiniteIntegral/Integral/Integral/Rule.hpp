//midpoint and simpson rule

#ifndef Rule_HPP
#define Rule_HPP
#define pi 3.141592653589793238462643

#include<cmath>
#include<iostream>

class Rule {
private:
	double start, end,thresh;
	int size;
public:
	Rule(double st_, double e_,double th_, int si_) :start(st_), end(e_),thresh(th_), size(si_) {}
	double GetH() const { return (end - start) / double(size); }
	void Size(int si_) { size = si_; }
	int Size() const { return size; }
	void Start(double st_) { start = st_; }
	double Start() const { return start; }
	void End(double e_) { end = e_; }
	double End() const { return end; }
	//to be specified
	double f(double x) { 
		return 1.0/std::sqrt(2.0*pi)*std::exp(-x*x/2.0) ; 
	}
	virtual double oneStep(double x) = 0;
	double GetIntegral();
};

class MidPoint :public Rule
{
private:
public:
	MidPoint(double st_,double e_,int si_,double th_):Rule(st_,e_,th_,si_){}
	//conduct computation
	double oneStep(double x);
};

class Simpson : public Rule
{
private:
public:
	Simpson(double st_,double e_,int si_,double th_):Rule(st_,e_,th_,si_){}
	//conduct computation
	double oneStep(double x);
};


#endif