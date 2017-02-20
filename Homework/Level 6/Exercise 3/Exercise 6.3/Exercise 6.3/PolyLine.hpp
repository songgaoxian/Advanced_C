//PolyLine.hpp
//
//declare class PolyLine

#ifndef PolyLine_HPP
#define PolyLine_HPP

#include<functional>

template<typename T,typename A,template<typename, typename>class Container>
class PolyLine
{
private:
	Container<T,A> points;
public:
	PolyLine();//constructor
	void Push(T& obj);//push to points
	int Size() const;//return number of points in Polyline
	void Display() const;//display contents of PolyLine
	T& Back() const;//return back of Polyline
	void Pop();//remove one element
	void Clear();//clear all elements
	virtual ~PolyLine() {}//destructor
};

#include"PolyLine.cpp"


#endif