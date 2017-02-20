//implement constructor in OptionData
#include"OptionData.hpp"
#include<algorithm>
#include<iostream>
#include<string>

OptionData::OptionData(std::tuple<double, double, double, double, double, double, char>& src) :R(std::get<0>(src)), V(std::get<1>(src)),
   Div(std::get<2>(src)), IC(std::get<3>(src)), T(std::get<4>(src)), K(std::get<5>(src)), type(std::get<6>(src)) 
{
	Disc = [=]()->double {return std::exp(-R*T); };
	if(type=='c'){
		//if the option is call
		Pay = [=](double St)->double {return std::max(St - K, 0.0); };    //St is the price at maturity
	}
	else {
		//the option is put
		Pay = [=](double St)->double {return std::max(K - St, 0.0); }; //St is the price at maturity
	}
}

void OptionData::OptionInfo() {
	std::cout << type << ":Drift is " << R << ",Volatility is " << V << ",Dividend is " << Div << ",IC is " << IC << ",T is " << T << ",K is " << K << '\n';
}
