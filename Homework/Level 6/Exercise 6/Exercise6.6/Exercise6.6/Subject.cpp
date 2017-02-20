//Subject.cpp
//
//implement Subject and derived classes
//written on 2016/7/2

#ifndef Subject_CPP
#define Subject_CPP

#include"Subject.hpp"

//implement Subject class
template<typename F,typename A,template<typename,typename>class Container>
Subject<F,A,Container>::Subject() {
	LongFormat = [&]() {
		Counter<F,A,Container>* sub_c = dynamic_cast<Counter<F,A,Container>*>(this);
		//set format
		std::cout.precision(0);
		//display long format value
		std::cout << sub_c->GetCounter() << '\n';
	};
	DoubleFormat = [&]() {
		Counter<F,A,Container>* sub_c = dynamic_cast<Counter<F,A,Container>*>(this);
		//set format
		std::cout.setf(std::ios::showpoint);
		std::cout.precision(2);
		std::cout.setf(std::ios::fixed);
		//display double format counter value
		std::cout << sub_c->GetCounter() << '\n';
	};
}
template<typename F,typename A,template<typename,typename>class Container>
void Subject<F,A,Container>::Attach(std::string choice) {
	if (choice == "long") {
		lst.push_back(LongFormat);
	}
	if (choice == "double") {
		lst.push_back(DoubleFormat);
	}
}
template<typename F,typename A,template<typename,typename>class Container>
void Subject<F,A,Container>::Detach() { lst.pop_back(); }

template<typename F,typename A,template<typename,typename>class Container>
void Subject<F,A,Container>::Notify() {
	for (auto it = lst.begin(); it != lst.end(); it++) {
		(*it)();
	}
}

//f)implement Counter class
template<typename F,typename A,template<typename,typename>class Container>
void Counter<F,A,Container>::IncreaseCounter(double increment) {
	value += increment;
	this->Notify();
}
//g)
template<typename F,typename A,template<typename,typename>class Container>
void Counter<F,A,Container>::DecreaseCounter(double decrement) {
	value -= decrement;
	this->Notify();
}

#endif