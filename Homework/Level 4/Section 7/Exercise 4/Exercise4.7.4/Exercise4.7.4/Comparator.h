//Comparator.h
//
//implement comparators for bimaps
//written on 2016/6/22

#ifndef Comparator_H
#define Comparator_H
#include<string>

template<typename T>
struct Greater {
	bool operator()(const T& t1, const T& t2) const {
		return t1 > t2;
	}
};

template<typename T>
struct Less {
	bool operator()(const T& t1, const T& t2) const {
		return t1 < t2;
	}
};

template<typename T>
struct Equal {
	bool operator()(const T& t1, const T& t2) const {
		return t1 == t2;
	}
};


#endif
