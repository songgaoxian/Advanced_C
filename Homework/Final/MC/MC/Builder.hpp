//Builder.hpp
//create builder classes

#ifndef Builder_HPP
#define Builder_HPP

#include"SDE.hpp"
#include"FDM.hpp"
#include"RNG.hpp"
#include"OptionData.hpp"
#include<iostream>


using T_Composite = std::tuple<std::shared_ptr<ISde>, std::shared_ptr<FdmBase>, std::shared_ptr<Rng>>;

//template MCBuilder: S represents pointer(Sde), F represents pointer(Fdm), R represents pointer(Rng)
template<typename S, typename F, typename R>
class MCBuilder {
private:
	double r; //drift
	double v; //volatility
	double d; //dividend
	double IC; //initial condition
	double T; //expiry
	double b;//beta
public:
	//constructor
	MCBuilder(OptionData& src,double b_);
	std::tuple<S, F, R> Parts(S sde, F fdm, R rng);
	T_Composite Parts();
	std::shared_ptr<ISde> GetSde();
	std::shared_ptr<Rng> GetRng();
	std::shared_ptr<FdmBase> GetFdm(std::shared_ptr<ISde> sde);
};

#include"Builder.cpp"
#endif