//SUD.cpp
//implement classes in SUD.hpp

#ifndef SUD_CPP
#define SUD_CPP

#include"SUD.hpp"
#include<iostream>

template<typename T1, typename T2,
	template<typename T1>class Source,
	template<typename T2>class Sink,
	template<typename T1, typename T2>class Processing>
void SUD<T1,T2,Source,Sink,Processing>::run() {
	auto s = message();
	auto s2=convert(s);
	print(s2);
	end();
}

template<typename T1>
T1 MySource<T1>::message() { return (T1)1.0; }

template<typename T1,typename T2>
T2 MyProcess<T1, T2>::convert(T1& s) const { return (T2)s; }

template<typename T2>
void MySink<T2>::print(T2& s) const { std::cout << s << '\n'; }

template<typename T2>
void MySink<T2>::end() const { std::cout << "end\n"; }


#endif