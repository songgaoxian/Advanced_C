//Observer.cpp
//
//implement Observer and derived classes
//written on 2016/7/2

#include"Observer.hpp"
#include"Subject.hpp"
//implement Update for LongFormat
void LongFormat::Update(Subject& sub) {
	Counter& sub_c = dynamic_cast<Counter&>(sub);
	//set format
	std::cout.precision(0);
	//display long format counter value
	std::cout << sub_c.GetCounter() << '\n';
}
//implement Update for DoubleFormat
void DoubleFormat::Update(Subject& sub) {
	Counter& sub_c = dynamic_cast<Counter&>(sub);
	//set format
	std::cout.setf(std::ios::showpoint);
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	//display double format counter value
	std::cout << sub_c.GetCounter() << '\n';
}
