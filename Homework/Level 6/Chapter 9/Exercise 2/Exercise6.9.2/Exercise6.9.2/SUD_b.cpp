//SUD_b.cpp
//implement classes defined in SUD_b.hpp

#ifndef SUD_b_CPP
#define SUD_b_CPP

#include"SUD_b.hpp"
#include<iostream>

template<typename T1,typename T2,
	template<typename T1>class Source,
	template<typename T2>class Sink>
SUD_b<T1,T2,Source,Sink>::SUD_b(const P_Func& proc):Process(proc){}

template<typename T1,typename T2,
	template<typename T1>class Source,
	template<typename T2>class Sink>
void SUD_b<T1, T2, Source, Sink>::run() {
	auto s = message();
	auto s2 = Process(s);
	print(s2);
	end();
}

template<typename T1>
T1 MySource_b<T1>::message() { return (T1)2.0; }

template<typename T2>
void MySink_b<T2>::print(T2& t) const { std::cout << t << '\n'; }

template<typename T2>
void MySink_b<T2>::end() const { std::cout << "end\n"; }

#endif