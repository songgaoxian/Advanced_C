//Mediator.hpp
//create mediator class

#ifndef Mediator_HPP
#define Mediator_HPP

#include<boost\signals2.hpp>
#include"Pricer.hpp"
#include"FDM.hpp"
#include"RNG.hpp"
#include"SDE.hpp"
#include"Builder.hpp"
#include"DefaultBuilder.hpp"
#include"Stopwatch.hpp"

using PathEvent=boost::signals2::signal<void(std::vector<double>& arr)>; //arr is the path of underlying asset
using EndOfSimulation=boost::signals2::signal<void()>; //signal that computation is finished

//MCMediator class
class MCMediator {
private:
	std::shared_ptr<ISde> sde;
	std::shared_ptr<FdmBase> fdm;
	std::shared_ptr<Rng> rng;
	long long NSim; //num of simulations
	std::vector<double> res;//generated path
	int id;//identify mediator
	StopWatch sw;//track the time for start()
public:
	PathEvent path; //sigmal to pricer to compute
	EndOfSimulation finish; //signal that computation ends
	//constructor
	MCMediator(T_Composite parts, long long numSimulation,int id_);
	//default constructor
	MCMediator() {}
	void start();
};


#endif