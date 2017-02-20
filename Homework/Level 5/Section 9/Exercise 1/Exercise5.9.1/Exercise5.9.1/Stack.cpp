//Stack.cpp
//
//implement Stack class
//written on 2016/7/2

#include"Stack.hpp"
#include"Singleton.hpp"
#include"State.hpp"

void Stack::Init(int size) {
	//check if size<1
	if (size < 1) size = 1;
	//create array with given size
	s_array = new int[size];
	//set current index 0
	index = 0;
	//set state to empty state
	state = EmptyState::Instance();
	arr_size = size;
}
Stack::Stack() { Init(1); }

Stack::Stack(int size) { Init(size); }

void Stack::Push(int element) { state->State(); state->Push(element, this); }

int Stack::Pop() { state->State(); return state->Pop(this); }

void Stack::ChangeState(StackState* s) { state = s; }