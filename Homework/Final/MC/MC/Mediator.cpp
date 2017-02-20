//Mediator.cpp
//implement methods in Mediator.hpp

#include"Mediator.hpp"



MCMediator::MCMediator(T_Composite parts, long long numSimulation,int id_) {
	id = id_;
	sde = std::get<0>(parts);
	fdm = std::get<1>(parts);
	rng = std::get<2>(parts);
	NSim = numSimulation;
	res.resize(fdm->NT);
}
void MCMediator::start() {
	sw.StartStopWatch();
	//main event loop for path generation
	double VOld, VNew; //store old value and new value
	std::tuple<double, double> randomVars; //store random variables
	double norm1, norm2;
	//calculate NSim paths
	for (long long i = 1; i <= NSim; ++i) {
		if ((i / 1000) * 1000 == i) {
			std::cout << i << " ";
			//print something
		}
		VOld = sde->InitialCondition();
		res[0] = VOld;
		//get one path
		for (unsigned int n = 1; n < res.size(); ++n) {
			randomVars = rng->GenerateRn();
			norm1 = std::get<0>(randomVars);
			norm2 = std::get<1>(randomVars);
			//compute value after 1 more step
			VNew = fdm->advance(VOld, fdm->x[n - 1], fdm->k, norm1, norm2);
			res[n] = VNew; VOld = VNew;
		}
		path(res);//run the signal
	}
	finish(); //run the finishing signal
	sw.StopStopWatch();
	//print out the running time
	std::cout << "Mediator " << id << " takes " << sw.GetTime() << " seconds\n";
}