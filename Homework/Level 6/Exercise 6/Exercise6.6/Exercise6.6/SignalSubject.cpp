//SignalSubject.cpp
//implement SignalSubject and derived classes

#include"SignalSubject.hpp"

SignalSubject::SignalSubject() {
	LongFormat = [&]() {
		SignalCounter* sub_c = dynamic_cast<SignalCounter*>(this);
		//set format
		std::cout.precision(0);
		//display long format value
		std::cout << sub_c->GetCounter() << '\n';
	};
	DoubleFormat = [&]() {
		SignalCounter* sub_c = dynamic_cast<SignalCounter*>(this);
		//set format
		std::cout.setf(std::ios::showpoint);
		std::cout.precision(2);
		std::cout.setf(std::ios::fixed);
		//display double format counter value
		std::cout << sub_c->GetCounter() << '\n';
	};
	sigNum = 0;
}

void SignalSubject::Attach(std::string choice) {
	//attach to lst
	if (choice == "long") {
		sigNum++;
		lst.connect(sigNum, LongFormat);
	}
	if (choice == "double") {
		sigNum++;
		lst.connect(sigNum, DoubleFormat);
	}
}

void SignalSubject::Detach() {
	lst.disconnect(sigNum); //detach the observer with highest group number
	sigNum--;
}
//run all attached observers
void SignalSubject::Notify(){lst();}

//implement SignalCounter
void SignalCounter::IncreaseCounter(double increment) { 
	value += increment; 
	this->Notify();
}
void SignalCounter::DecreaseCounter(double decrement) {
	value -= decrement;
	this->Notify();
}
