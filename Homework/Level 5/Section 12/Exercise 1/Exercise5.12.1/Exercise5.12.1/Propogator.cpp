//Propogator.cpp
//
//implement classes defined in Propogator.h
//written on 2016/7/2
#include"Propogator.hpp"

void Observable::AddObserver(Observer* obs) {
	lst.push_back(obs);
}
void Observable::DeleteObserver() { lst.pop_back(); }
void Observable::NotifyObservers() {
	for (auto it = lst.begin(); it != lst.end(); it++) {
		(*it)->Update(*this);
	}
}