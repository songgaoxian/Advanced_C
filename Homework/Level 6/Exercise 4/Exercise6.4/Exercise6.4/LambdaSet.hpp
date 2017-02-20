//LambdaSet.hpp
//
//implement some lambda functions
//written on 2016/7/14

#ifndef LambdaSet_HPP
#define LambdaSet_HPP

#include"TmpProcessor.hpp"
#include<iostream>
//some simple lambda functions
FactoryFunction<int> factory = []()->int {
	return std::rand() % 35;
};

ComputeFunction<int> compute = [](const int& val)->int {
	return val * 10;
};

DispatchFunction<int> dispatch = [](int& val) {std::cout << "Value=" << val << '\n'; };



#endif
