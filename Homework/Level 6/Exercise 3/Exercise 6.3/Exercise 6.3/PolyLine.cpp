//PolyLine.cpp
//
//implement PolyLine class

#ifndef PolyLine_CPP
#define PolyLine_CPP

#include"PolyLine.hpp"
#include<iostream>

template<typename T,typename A, template<typename,typename>class Container>
PolyLine<T,A,Container>::PolyLine(){}

template<typename T,typename A, template<typename,typename>class Container>
void PolyLine<T,A,Container>::Push(T& obj) { 
	points.push_back(obj);
}

template<typename T,typename A,template<typename,typename>class Container>
int PolyLine<T,A,Container>::Size() const { return points.size(); }

template<typename T, typename A, template<typename, typename>class Container>
void PolyLine<T, A, Container>::Display() const { 
	std::cout << "\nPolyLine:";
	for (auto it = points.begin(); it != points.end(); it++) {
		std::cout << *it << ";";
	}
}

template<typename T,typename A,template<typename,typename>class Container>
T& PolyLine<T,A,Container>::Back() const { return points.back(); }

template<typename T,typename A,template<typename,typename>class Container>
void PolyLine<T,A,Container>::Pop() { points.pop_back(); }

template<typename T,typename A, template<typename,typename>class Container>
void PolyLine<T,A,Container>::Clear() { points.clear(); }

#endif
