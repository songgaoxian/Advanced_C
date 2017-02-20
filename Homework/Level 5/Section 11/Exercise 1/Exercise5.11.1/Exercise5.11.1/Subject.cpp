//Subject.cpp
//
//implement Subject and derived classes
//written on 2016/7/2

#include"Observer.hpp"
#include"Subject.hpp"
//implement Subject class
void Subject::Attach(Observer* obs) {
	lst.push_back(obs);
}
void Subject::Detach() { lst.pop_back(); }
void Subject::Notify() {
	for (auto it = lst.begin(); it != lst.end(); it++) {
		(*it)->Update(*this);
	}
}

//f)implement Counter class
void Counter::IncreaseCounter(double increment) { 
	value += increment; 
	this->Notify();
}
//g)
void Counter::DecreaseCounter(double decrement) {
	value -= decrement;
	this->Notify();
}
