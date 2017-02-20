//State.cpp
//
//implement state classes
//written on 2016/7/2

#include"State.hpp"

void StackState::Push(int element,Stack* stk){
	stk->s_array[stk->index] = element;
	stk->index++;
}
int StackState::Pop(Stack* stk) {
	stk->index--;
	return stk->s_array[stk->index];
}

void EmptyState::Push(int element, Stack* stk) {
	this->StackState::Push(element, stk);
	//check how to change state
	if (stk->Index() == stk->Size()) {
		stk->ChangeState(FullState::Instance());
	}
	else {
		stk->ChangeState(NotFullNotEmptyState::Instance());
	}
}

void NotFullNotEmptyState::Push(int element, Stack* stk) {
	this->StackState::Push(element, stk);
	//check if need to change state
	if (stk->Size() == stk->Index()) {
		stk->ChangeState(FullState::Instance());
	}
}
int NotFullNotEmptyState::Pop(Stack* stk) {
	//check if need to change to empty state
	if (stk->Index() == 1) stk->ChangeState(EmptyState::Instance());
	return this->StackState::Pop(stk);
}

int FullState::Pop(Stack* stk) {
	//change state
	if (stk->Index() == 1) {
		stk->ChangeState(EmptyState::Instance());
	}
	else {
		stk->ChangeState(NotFullNotEmptyState::Instance());
	}
	return this->StackState::Pop(stk);
}