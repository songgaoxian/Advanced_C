//FDM.hpp
//set finite difference method

#ifndef FDM_HPP
#define FDM_HPP

#include"SDE.hpp"
#include<memory>
#include<vector>

//base class of FDM and its interface
class FdmBase
{
protected:
	std::shared_ptr<ISde> sde; //the stochastic differential equation
public:
	unsigned int NT; //number of subdivisions
	std::vector<double> x; //mesh array
	double k; //mesh size

	FdmBase(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions); //constructor

	virtual std::shared_ptr<ISde> StochasticEquation() const; //getter of Stochastic equation
	virtual void StochasticEquation(std::shared_ptr<ISde> isd);//setter of Stochastic equation
	virtual double advance(double xn, double tn, double dt, double WienerIncrement, double WienerIncrement2) = 0;
	//advance 1 step in FDM computation from xn
};

//explicit Euler finite difference scheme
class EulerFdm :public FdmBase
{
public:
	EulerFdm(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions);
	double advance(double xn, double tn, double dt, double normalVar, double normalVar2);
};

//Milstein scheme
class MilsteinFdm : public FdmBase
{
public:
	MilsteinFdm(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions);
	double advance(double xn, double tn, double dt, double normalVar, double normalVar2);
};

//ModifiedPredictorCorrectorFdm scheme
class ModifiedPredictorCorrectorFdm :public FdmBase
{
private:
	double A, B, VMid;
public:
	ModifiedPredictorCorrectorFdm(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions, double a, double b);
	double advance(double xn, double tn, double dt, double normalVar, double normalVar2);
};


#endif