//CombinerSlot.h
//
//create combiner BootstrapCheck and slots
//written on 2016/6/23
#ifndef CombinerSlot_H
#define CombinerSlot_H
#include<iostream>

struct BootstrapCheck {
	//iterator slots and return first false; 
	//otherwise, return true
	typedef bool result_type;
	template<typename InputIterator>
	bool operator()(InputIterator first, InputIterator last) const
	{
		while (first != last) {
			if (!*first) {
				return false;
			}
			++first;
		}
		return true;
	}

};

//b)create three slots
bool slot1() { std::cout << "Slot1\n"; return true; }
bool slot2() { std::cout << "Slot2\n"; return false; }
bool slot3() { std::cout << "Slot3\n"; return true; }

#endif


