//SDE.hpp
//model the stochastic differential equation

#ifndef SDE_HPP
#define SDE_HPP

#include"OptionData.hpp"
#include<math.h>

//base class of SDE, which is like an interface
class ISde
{
public:	
	virtual double Drift(double x, double t)=0; //model the drift term
	virtual double Diffusion(double x, double t) = 0; //model diffusion term
	virtual double DriftCorrected(double x, double t, double B) = 0; //model drift corrected term
	virtual double DiffusionDerivative(double x, double t) = 0; //model the derivative of diffusion
	virtual double InitialCondition() const = 0; //getter of initial condition
	virtual void InitialCondition(double x) = 0; //setter of initial condition
	virtual double Expiry() const = 0; //getter of expiry time
	virtual void Expiry(double t) = 0;//setter of expiry time
};

//class of geometric brownion motion
class GBM : public ISde
{
protected:
	double mu; //drift
	double vol; //const volatility
	double d; //const dividend yield
	double ic; //initial condition
	double exp; //expiry
public:
	GBM(OptionData& src); //constructor
	GBM(double mu_, double vol_, double d_, double ic_, double exp_);//another constructor
	virtual double Drift(double x, double t);
	virtual double Diffusion(double x, double t);
	virtual double DiffusionDerivative(double x, double t);

    double DriftCorrected(double x, double t, double B);
	double InitialCondition() const;
	void InitialCondition(double x);
	double Expiry() const;
	void Expiry(double t);
};

//class of customized GBM: Drift and Diffusion are also related to t
class CustomizedGBM:public GBM
{
public:
	CustomizedGBM(OptionData& src);
	CustomizedGBM(double mu_, double vol_, double d_, double ic_, double exp_);//another constructor
	double Drift(double x, double t) override;
	double Diffusion(double x, double t) override;
	double DiffusionDerivative(double x, double t) override;
};

class CEV :public ISde
{ // CEV model
private:
    double mu;   // r
    double vol;  // Constant volatility
	double d;    // Constant dividend yield
    double ic;   // Initial condition
	double exp;  // Expiry
	double b;    // Beta
public:
	CEV(double mu_, double vol_, double d_, double ic_, double exp_, double b_);//constructor
	CEV(OptionData& src, double b_);//another constructor
	double Drift(double x, double t);
	double Diffusion(double x, double t);
	double DriftCorrected(double x, double t, double B);

	double DiffusionDerivative(double x, double t);
	double InitialCondition() const;
	void InitialCondition(double x);
	double Expiry() const;
	void Expiry(double t);
};
	

#endif