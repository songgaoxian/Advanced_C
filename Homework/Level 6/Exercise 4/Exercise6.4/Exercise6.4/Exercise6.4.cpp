//Exercise6.4.cpp
//
//test TmpProcessor
//written on 2016/7/14

#include"TmpProcessor.hpp"
#include"LambdaSet.hpp"
#include"Stock.hpp"
#include<iostream>
#include<vector>
#include<future>
#include<algorithm>

int Trials = 200;
double sum_payoff = 0;

void calculateStock(FactoryFunction<Stock> f, ComputeFunction<Stock> c, DispatchFunction<Stock> d) {
	TmpProcessor<Stock> tmpStock(f, c, d);
	tmpStock.algorithm();
}

int main() {
	//a simple example
	//create TmpProcessor
	TmpProcessor<int> tmpInt(factory, compute, dispatch);
	//run the algorithm
	tmpInt.algorithm();

	//start the complex one
	//compute the price
	//specify the functions
	FactoryFunction<double> factory_double = []()->double {
		//specify functions
		FactoryFunction<Stock> factory_stock = []()->Stock {return Stock(); };
		ComputeFunction<Stock> compute_stock = [](const Stock& stk)->Stock {
			Stock result(stk);
			while (result.T() <= result.Expire()) {
				result.advance();
			}
			return result;
		};
		//assume the option is call
		DispatchFunction<Stock> dispatch_stock = [](Stock& stk) {sum_payoff += std::max<double>(stk.S() - stk.K(), 0.0); };

		//simulate 200 times
		std::vector<std::future<void>> threads(Trials);
		for (int i = 0; i < Trials; ++i) {
			threads[i] = std::async(calculateStock, factory_stock, compute_stock, dispatch_stock);
		}
		for (int i = 0; i < Trials; ++i) { threads[i].wait(); }
		return sum_payoff; 
	};
	ComputeFunction<double> compute_double = [](const double& val)->double {
		double interest = 0.08;
		double discount = std::exp(-interest);
		double result = val*discount/(double)Trials;
		return result;
	};
	DispatchFunction<double> dispatch_double = [](double& val) {std::cout << "\ncall price is " << val<<'\n'; };
	TmpProcessor<double> tmpDouble(factory_double, compute_double, dispatch_double);
	tmpDouble.algorithm();
	//end of parallel implementation

	//sequential version
	sum_payoff = 0;
	FactoryFunction<double> factory_double_sequential = []()->double {
		//specify functions
		FactoryFunction<Stock> factory_stock = []()->Stock {return Stock(); };
		ComputeFunction<Stock> compute_stock = [](const Stock& stk)->Stock {
			Stock result(stk);
			while (result.T() <= result.Expire()) {
				result.advance();
			}
			return result;
		};
		//assume the option is call
		DispatchFunction<Stock> dispatch_stock = [](Stock& stk) {sum_payoff += std::max<double>(stk.S() - stk.K(), 0.0); };

		//simulate 200 times
		for (int i = 0; i < Trials; ++i) {
			calculateStock(factory_stock, compute_stock, dispatch_stock);
		}
		return sum_payoff;
	};
	//sequential TmpProcessor
	TmpProcessor<double> tmpDouble_Sequential(factory_double_sequential, compute_double, dispatch_double);
	tmpDouble_Sequential.algorithm();
	
	return 0;
}