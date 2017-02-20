//Stack.h
//
//create Stack and States classes
//written on 2016/7/1

#ifndef Stack_H
#define Stack_H

#include<iostream>
#include<string>
#include"Singleton.hpp"

//a)create stack
class Stack {
friend class StackState;
friend class EmptyState;
friend class NotFullNotEmptyState;
friend class FullState;
private:
	//b)use array to store elements
	int* s_array;
	//c)current index
	int index;
	//size of array
	int arr_size;
	//d)current state
	StackState* state;
	//e)Init
	void Init(int size);

public:
	//f)default constructor
	Stack();
	//g)constructor with size argument
	Stack(int size);
	//h)create push
	void Push(int element);
	//i)create pop
	int Pop();
	//give array size
	int Size() const { return arr_size; }
	//give current index
	int Index() const { return index; }
	//change state
	void ChangeState(StackState* s);
};

#include"State.hpp"

#endif
