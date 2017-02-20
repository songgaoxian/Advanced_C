//Subject.h
//
//implement Subject class and some slots
//written on 2016/6/23
#ifndef Subject_H
#define Subject_H
#include<boost/function.hpp>
#include<boost/signals2.hpp>
#include<iostream>
typedef boost::function<void(double)> FunctionType;
//a)
class Subject {
private:
	boost::signals2::signal<void(double)> attentionSig;
	int group;
public:
	Subject() { group = 0; }
	void AddObserver(const FunctionType& ft) { 
		//connect ft to attentionSig
		attentionSig.connect(group, ft);
		//specify next group number
		group++;
	}
	void ChangeEvent(double x) {
		//emit attentionSig
		attentionSig(x);
	}
	
};

//b)create slots
void CPrint(double x) { std::cout << "C function: " << x << std::endl; }
struct Print {
	void operator()(double x) { std::cout << "I am a printer " << x << std::endl; }
};
struct MathsWhiz {
	double val;
	//constructor
	MathsWhiz(double x) { val = x; }
	//implement operator
	void operator()(double x) { std::cout << "MathsWhiz: " << x + val << '\n'; }
};
struct Database {
	void operator()(double x) { std::cout << "Database: " << x << '\n'; }
};



#endif
