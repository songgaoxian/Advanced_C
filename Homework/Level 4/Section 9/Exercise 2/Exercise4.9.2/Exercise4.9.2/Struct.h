//Struct.h
//
//create a class, MyStruct to be used
//written on 2016/6/23

#ifndef Struct_H
#define Struct_H
#include<iostream>
//copied
struct MyStruct {
	double val;
	MyStruct(double v) { val = v; }
	void modify(double newValue) {
		val = newValue;
		std::cout << "A third slot " << val << std::endl;
	}
};
#endif
