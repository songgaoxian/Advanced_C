//PolyLineFactory.cpp
//
//implement PolyLineFactory

#ifndef PolyLineFactory_CPP
#define PolyLineFactory_CPP

#include"PolyLineFactory.hpp"
#include<iostream>

template<typename T,typename A,typename S,template<typename,typename>class Container>
PolyLineFactory<T,A,S, Container>::PolyLineFactory(const Creator<S>& c) {
	create = c;
}

template<typename T,typename A, typename S,template<typename,typename>class Container>
PolyLine<T,A,Container>* PolyLineFactory<T,A,S,Container>::CreatePolyLine() {
	std::cout << "\nLet's create a PolyLine\n";
	std::cout << "How many points are in the polyline?";
	//get how many points to create
	int Num;
	std::cin >> Num;
	//declare pointer to PolyLine
	PolyLine<T,A, Container>* poly = new PolyLine<T,A,Container>();
	//create polyline
	for (int i = 0; i < Num; ++i) {
		T obj = *dynamic_cast<T*>(create());
		poly->Push(obj);
	}
	return poly;
}
#endif