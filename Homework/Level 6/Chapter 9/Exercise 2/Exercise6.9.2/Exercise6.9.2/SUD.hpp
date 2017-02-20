//SUD.hpp
//declare class SUD and related classes

#ifndef SUD_HPP
#define SUD_HPP

template<typename T1, typename T2,
	template<typename T1>class Source,
	template<typename T2>class Sink,
	template<typename T1, typename T2>class Processing>
class SUD:private Source<T1>,private Sink<T2>,private Processing<T1,T2>
{
private:
	using Source<T1>::message; //get input
	using Processing<T1, T2>::convert; //convert input to output
	using Sink<T2>::print; //produce output
	using Sink<T2>::end; //end of program
public:
	void run();
};

template<typename T1>
class MySource
{
public:
	T1 message();
};

template<typename T1,typename T2>
class MyProcess
{
public:
	T2 convert(T1& s) const;
};

template<typename T2>
class MySink
{
public:
	void print(T2& s) const;
	void end() const;

};
#include"SUD.cpp"
#endif