//declare class to compute BS

#ifndef BS_HPP
#define BS_HPP

#include"Rule.hpp"

class BS {
protected:
	double s, k, r, q, sigma, t;
	Simpson simp;
public:
	BS(double s_, double k_, double r_, double q_, double sig, double t_, Simpson sp) :s(s_), k(k_), r(r_), q(q_), sigma(sig), t(t_),simp(sp) {}
	double S() const { return s; }
	void S(double s_) { s = s_; }
	double K() const { return k; }
	void K(double k_) { k = k_; }
	double R() const { return r; }
	void R(double r_) { r = r_; }
	double Q() const { return q; }
	void Q(double q_) { q = q_; }
	double Sigma() const { return sigma; }
	void Sigma(double sig_) { sigma = sig_; }
	double T() const { return t; }
	void T(double t_) { t = t_; }
	virtual double Price() = 0;
	virtual double Delta() = 0;
	virtual double Vega() = 0;
};

class Call : public BS
{
public:
	Call(double s_, double k_, double r_, double q_, double sig, double t_,Simpson sp) :BS(s_, k_,r_,q_, sig, t_,sp) {}
	double Price();
	double Delta();
	double Vega();
};



#endif