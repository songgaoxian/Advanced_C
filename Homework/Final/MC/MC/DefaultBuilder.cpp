//implement DefaultBuilder class and builder factory class

#include"DefaultBuilder.hpp"
//DefaultBuilder
DefaultBuilder::DefaultBuilder(OptionData& src) :r(src.R), v(src.V), d(src.Div), IC(src.IC), T(src.T) {}

T_Composite DefaultBuilder::Parts() {
	//create sde
	std::shared_ptr<ISde> sde;
	sde.reset(new GBM(r, v, d, IC, T));
	//create fdm
	std::shared_ptr<FdmBase> fdm;
	fdm.reset(new EulerFdm(sde, 500));
	//create rng
	std::shared_ptr<Rng> rng;
	rng.reset(new LibRandom(Rand<std::normal_distribution<double>>));
	//create result
	T_Composite result(sde, fdm, rng);
	return result;
}
DefaultBuilder& DefaultBuilder::operator=(const DefaultBuilder& src) {
	r = src.r;
	v = src.v;
	d = src.d;
	IC = src.IC;
	T = src.T;
	return *this;
}
//end

//implement builder factory
T_Composite BuilderFactory::ImplementBuilder(OptionData& option, double beta) {
	std::cout << "\n-------Choose builder------\n";
	std::cout << "choose 1=MCBuilder, others=DefaultBuilder\n";
	//get choice
	int choice;
	std::cin >> choice;

	MCBuilder<std::shared_ptr<ISde>, std::shared_ptr<FdmBase>, std::shared_ptr<Rng>> mcbuilder(option, beta);
	DefaultBuilder dbuilder(option);
	//return appropriate parts
	if (choice == 1) {
		std::cout << "Selected MCBuilder\n";
		return mcbuilder.Parts();
	}
	else {
		std::cout << "Selected DefaultBuilder\n";
		return dbuilder.Parts();
	}
}