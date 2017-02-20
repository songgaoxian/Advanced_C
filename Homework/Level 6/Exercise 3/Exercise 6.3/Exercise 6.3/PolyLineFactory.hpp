//PolyLineFactory.hpp
//
//implement factory method for PolyLine

#ifndef PolyLineFactory_HPP
#define PolyLineFactory_HPP

#include"PolyLine.hpp"

template<typename S>
using Creator = std::function<S*()>; //create shapes

template<typename T,typename A, typename S, template<typename,typename>class Container>
class PolyLineFactory {
private:
	Creator<S> create;
public:
	PolyLineFactory(const Creator<S>& c);//constructor
	PolyLine<T,A,Container>* CreatePolyLine();//create polyline
};

#include"PolyLineFactory.cpp"

#endif
