//Slots.h
//
//create slots from free function, lambda function and function object
//written on 2016/6/23
#ifndef Slots_H
#define Slots_H
#include<boost/signals2.hpp>
#include<iostream>

//a)Create slots
//stored lambda function
auto slot1 = []() {std::cout << "Slot1, created by lambda function\n"; };

//free function
void slot2() { std::cout << "Slot2, created by free function\n"; }

//function object
struct slot3 {
	slot3() {}
	void operator()() const { std::cout << "Slot3, created by function object\n"; }
};

//d)
//create slot S1
void S1() { std::cout << "This is S1\n"; }
//create slot S2
void S2() { std::cout << "This is S2\n"; }
//create slot S3
void S3() { std::cout << "This is S3\n"; }
//create slot S4
void S4() { std::cout << "This is S4\n"; }




#endif

