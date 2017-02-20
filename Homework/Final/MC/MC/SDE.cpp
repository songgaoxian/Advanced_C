//SDE.cpp
//implement methods in SDE class

#include"SDE.hpp"
#include<cmath>
//implement GBM
GBM::GBM(OptionData& src) :
	mu(src.R), vol(src.V), d(src.Div), ic(src.IC), exp(src.T) {}

GBM::GBM(double mu_, double vol_, double d_, double ic_, double exp_) : mu(mu_), vol(vol_), d(d_), ic(ic_), exp(exp_) {}

double GBM::Drift(double x, double t) { return (mu - d)*x; }

double GBM::Diffusion(double x, double t) { return vol*x; }

double GBM::DriftCorrected(double x, double t, double B) { return Drift(x, t) - B*Diffusion(x, t)*DiffusionDerivative(x, t); }

double GBM::DiffusionDerivative(double x, double t) { return vol; }

double GBM::InitialCondition() const { return ic; }
void GBM::InitialCondition(double x) { ic = x; }
double GBM::Expiry() const { return exp; }
void GBM::Expiry(double x) { exp = x; }
//end

//implement CustomizedGBM
CustomizedGBM::CustomizedGBM(OptionData& src):
	GBM(src){}

CustomizedGBM::CustomizedGBM(double mu_, double vol_, double d_, double ic_, double exp_):GBM(mu_,vol_,d_,ic_,exp_){}

double CustomizedGBM::Drift(double x, double t) { 
	return (mu - d)*x*t / exp; //a customized function(x,t) to compute drift
}
double CustomizedGBM::Diffusion(double x, double t) { return vol*x*std::sqrt(1.0 - t / exp); }//customized function(x,t) to get diffusion
double CustomizedGBM::DiffusionDerivative(double x, double t) { return vol*std::sqrt(1.0 - t / exp); }
//end

//implement CEV model
CEV::CEV(double mu_, double vol_, double d_, double ic_, double exp_, double b_):mu(mu_), b(b_), ic(ic_), vol(vol_ * std::pow(ic_, 1.0 - b_)),
                                                                                 d(d_), exp(exp_)
{}
CEV::CEV(OptionData& src, double b_) : mu(src.R), vol(src.V*std::pow(src.IC, 1.0 - b_)), d(src.Div), ic(src.IC), exp(src.T), b(b_) {}
double CEV::Drift(double x, double t) { return (mu - d) * x; }
double CEV::Diffusion(double x, double t) { return vol * std::pow(x, b); }
double CEV::DriftCorrected(double x, double t, double B){return Drift(x, t) - B * Diffusion(x, t) * DiffusionDerivative(x, t);}
double CEV::DiffusionDerivative(double x, double t)
{
	if (b > 1.0)
	{
		return vol * b * std::pow(x, b - 1.0);
	}
	else
	{
		return vol * b / std::pow(x, 1.0 - b);
	}
}
double CEV::InitialCondition() const { return ic; }
void CEV::InitialCondition(double x) { ic = x; }
double CEV::Expiry() const { return exp; }
void CEV::Expiry(double x) { exp = x; }