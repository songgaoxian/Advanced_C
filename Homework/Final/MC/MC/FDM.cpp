//FDM.cpp
//implement classes' methods

#include"FDM.hpp"
//implement FdmBase
FdmBase::FdmBase(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions) : sde(stochasticEquation), NT(numSubdivisions) {
	k = sde->Expiry() / (double)NT;
	x.resize(NT + 1);
	//create mesh array
	x[0] = 0.0;
	for (unsigned int n = 1; n < x.size(); ++n) {
		x[n] = x[n - 1] + k;
	}
}

std::shared_ptr<ISde> FdmBase::StochasticEquation() const { return sde; }
void FdmBase::StochasticEquation(std::shared_ptr<ISde> isd) { sde = isd; }
//end

//EulerFdm
EulerFdm::EulerFdm(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions):FdmBase(stochasticEquation,numSubdivisions){}
double EulerFdm::advance(double xn, double tn, double dt, double normalVar, double normalVar2){
	return xn + sde->Drift(xn, tn)*dt + sde->Diffusion(xn, tn)*std::sqrt(dt)*normalVar;
}
//end

//MilsteinFdm
MilsteinFdm::MilsteinFdm(std::shared_ptr<ISde> stochasticEquation, unsigned int numSubdivisions):FdmBase(stochasticEquation,numSubdivisions){}
double MilsteinFdm::advance(double xn, double tn, double dt, double normalVar, double normalVar2) {
	return xn + sde->Drift(xn, tn)*dt + sde->Diffusion(xn, tn)*std::sqrt(dt)*normalVar + 0.5*dt*sde->Diffusion(xn, tn)*sde->DiffusionDerivative(xn, tn)*(normalVar*normalVar - 1.0);
}
//end

//ModifiedPredictorCorrectorFdm
ModifiedPredictorCorrectorFdm::ModifiedPredictorCorrectorFdm(std::shared_ptr<ISde> stochasticEquation,unsigned int numSubdivisions,double a,double b):FdmBase(stochasticEquation,numSubdivisions),A(a),B(b){}
double ModifiedPredictorCorrectorFdm::advance(double xn, double tn, double dt, double normalVar, double normalVar2) {
	//Euler for predictor
	VMid = xn + sde->Drift(xn, tn)*dt + sde->Diffusion(xn, tn)*std::sqrt(dt)*normalVar;
	//Modified Trapezoidal rule
	double driftTerm = (A*sde->DriftCorrected(VMid, tn + dt, B) + ((1.0 - A)*sde->DriftCorrected(xn, tn, B)))*dt;
	double diffusionTerm = (B*sde->Diffusion(VMid, tn + dt) + ((1.0 - B)*sde->Diffusion(xn, tn)))*std::sqrt(dt)*normalVar;
	return xn + driftTerm + diffusionTerm;
}