//SUD_b.hpp
//create classes for SUD required in b)

#ifndef SUD_b_HPP
#define SUD_b_HPP

#include<functional>

template<typename T1,typename T2,
	template<typename T1>class Source,
	template<typename T2>class Sink>
class SUD_b:private Source<T1>,private Sink<T2>
{
private:
	using P_Func = std::function<T2(const T1& t)>;
	P_Func Process;
	using Source<T1>::message;
	using Sink<T2>::print;
	using Sink<T2>::end;
public:
	SUD_b(const P_Func& proc);
	void run();
};

template<typename T1>
class MySource_b
{
public:
	T1 message();
};

template<typename T2>
class MySink_b
{
public:
	void print(T2& t) const;
	void end() const;
};

#include"SUD_b.cpp"
#endif