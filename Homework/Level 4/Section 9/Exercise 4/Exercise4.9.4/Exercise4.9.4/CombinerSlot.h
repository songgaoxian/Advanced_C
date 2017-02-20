//CombinerSlot.h
//
//implement Combiner for sum up operation and slots
//written on 2016/6/23

#ifndef CombinerSlot_H
#define CombinerSlot_H
#include<iostream>

//a)create slot 1
double slot1(double x, double y) {
	double result = x*y;
	std::cout << "result of slot1=" << result << '\n';
	return result;
}
//create slot 2
double slot2(double x, double y) {
	double result = x + 2.1*y;
	std::cout << "result of slot2=" << result << '\n';
	return result;
}
//create slot 3
double slot3(double x, double y) {
	double result = x + x*y / 1.9;
	std::cout << "result of slot3=" << result << '\n';
	return result;
}

//b)create SumCombiner
template<typename T>
struct SumCombiner {
	typedef T result_type;

	template<typename InputIterator>
	T operator()(InputIterator start, InputIterator end) {
		//initialize num_sum
		T num_sum = 0.0;
		while (start != end) {
			//sum up
			num_sum += *start;
			start++;
		}
		return num_sum;
	}

};



#endif
