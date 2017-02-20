//Singleton.cpp
//
//specify methods of Singleton class
//written on 2016/6/29
#ifndef Singleton_cpp
#define Singleton_cpp
#include"Singleton.hpp"

template<class TYPE> TYPE* Singleton<TYPE>::ins = NULL;
template<class TYPE> Destroyer<TYPE> Singleton<TYPE>::des;

template<class TYPE>
Singleton<TYPE>::Singleton(){}//default constructor

template<class TYPE>
Singleton<TYPE>::Singleton(const Singleton<TYPE>& src) {}//copy constructor

template<class TYPE>
Singleton<TYPE>::~Singleton() {
	//destructor
	int x; x = 0;
}


template<class TYPE>
TYPE* Singleton<TYPE>::instance() {
	//return the singleton instance
	if (ins == NULL) {
		ins = new TYPE;
		des.doomed(ins);
	}
	return ins;
}

template<class TYPE>
Singleton<TYPE>& Singleton<TYPE>::operator=(const Singleton<TYPE>& src) {
	return *this;
}
#endif