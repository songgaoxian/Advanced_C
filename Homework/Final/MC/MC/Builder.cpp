//Builder.cpp
//implement methods of builder classes

#ifndef Builder_CPP
#define Builder_CPP

#include"Builder.hpp"

template<typename S, typename F, typename R>
MCBuilder<S, F, R>::MCBuilder(OptionData& src,double b_): r(src.R),v(src.V),d(src.Div),IC(src.IC),T(src.T),b(b_){}

template<typename S,typename F,typename R>
std::tuple<S, F, R> MCBuilder<S, F, R>::Parts(S sde, F fdm, R rng) {
	std::tuple<S, F, R> result(sde, fdm, rng);
	return result;
}
template<typename S,typename F,typename R>
T_Composite MCBuilder<S, F, R>::Parts() {
	std::shared_ptr<ISde> sde = GetSde();
	std::shared_ptr<Rng> rng = GetRng();
	std::shared_ptr<FdmBase> fdm = GetFdm(sde);
	//create the result tuple
	T_Composite result(sde, fdm, rng);
	return result;
}
template<typename S,typename F,typename R>
std::shared_ptr<ISde> MCBuilder<S, F, R>::GetSde() {
	std::shared_ptr<ISde> result;
	std::cout << "\n------Create SDE------\n";
	std::cout << "choose 1=GBM, 2=CEV, others=CustomizedGBM\n";
	//get choice from user
	int choice;
	std::cin >> choice;
	
	if (choice == 1) {
		//set the pointer to GBM
		result.reset(new GBM(r, v, d, IC, T));
	}
	else if (choice == 2) {
		result.reset(new CEV(r, v, d, IC, T, b));
	}
	else
	{
		//set the pointer to CustomizedGBM
		result.reset(new CustomizedGBM(r, v, d, IC, T));
	}
	return result;
}
template<typename S,typename F,typename R>
std::shared_ptr<Rng> MCBuilder<S, F, R>::GetRng() {
	std::shared_ptr<Rng> result;
	std::cout << "\n------Create Rng------\n";
	std::cout << "choose 1=LibRandom, 2=BoxMuller,others=PolarMarsaglia\n";
	//get choice
	int choice;
	std::cin >> choice;
	
	switch (choice) {
	case 1:
		result.reset(new LibRandom(Rand<std::normal_distribution<double>>));
		break;
	case 2:
		result.reset(new BoxMuller(Rand<std::uniform_real_distribution<double>>));
		break;
	default:
		result.reset(new PolarMarsaglia(Rand<std::uniform_real_distribution<double>>));
		break;
	}
	return result;
}
template<typename S,typename F,typename R>
std::shared_ptr<FdmBase> MCBuilder<S, F, R>::GetFdm(std::shared_ptr<ISde> sde) {
	std::shared_ptr<FdmBase> result;
	std::cout << "\n------Create FDM------\n";
	std::cout << "choose 1=Euler, 2=Milstein, others=PredictorCorrector\n";
	//get choice
	int choice;
	std::cin >> choice;
    //get how many subdivisions, default to 500
	unsigned int NT=1000;
	std::cout << "How many subdivisions?\n";
	std::cin >> NT;
	
	double a = 0.5, b = 0.5;
	switch (choice) {
	case 1:
		result.reset(new EulerFdm(sde, NT));
		break;
	case 2:
		result.reset(new MilsteinFdm(sde, NT));
		break;
	default:
		result.reset(new ModifiedPredictorCorrectorFdm(sde, NT, a, b));
		break;
	}
	return result;
}

#endif