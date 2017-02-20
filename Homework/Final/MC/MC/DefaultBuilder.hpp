//use as default builder for pricing
//declare buider factory class to deliver builder

#ifndef DefaultBuilder_HPP
#define DefaultBuilder_HPP

#include"Builder.hpp"

class DefaultBuilder
{
private:
	double r; //drift
	double v; //volatility
	double d; //dividend
	double IC; //initial condition
	double T; //expiry
public:
	DefaultBuilder(OptionData& src);//constructor
	DefaultBuilder() {}//default constructor
	DefaultBuilder& operator=(const DefaultBuilder& src);
	T_Composite Parts();
};

class BuilderFactory {
public:
	BuilderFactory(){}//default constructor
					  //implement Builder
	T_Composite ImplementBuilder(OptionData& option, double beta);
};

#endif

