//State.h
//
//create State classes
//written on 2016/7/2

#ifndef State_H
#define State_H

#include<iostream>
#include<string>
#include"Stack.hpp"
#include"Singleton.hpp"

//j)implement StackState
class StackState
{
	friend class Singleton<StackState>;
public:
	//implement Push
	virtual void Push(int element, Stack* stk);
	//implement Pop
	virtual int Pop(Stack* stk);
	virtual void State() = 0;
};

//k)implement EmptyState
class EmptyState :public StackState
{
	friend class Singleton<EmptyState>;
public:
	//k)implement Push
	void Push(int element, Stack* stk) override;
	//implement Pop for EmptyState
	int Pop(Stack* stk) override {
		throw std::string("Cannot Pop from Empty Stack\n");
	}
	void State() { std::cout << "Empty State\n"; }
	static EmptyState* Instance() { return Singleton<EmptyState>::instance(); }
};

//l)implement NotFullNotEmptyState
class NotFullNotEmptyState :public StackState
{
	friend class Singleton<NotFullNotEmptyState>;
public:
	void Push(int element, Stack* stk) override;
	int Pop(Stack* stk) override;
	void State() { std::cout << "Not full Not Empty state\n"; }
	static NotFullNotEmptyState* Instance() { return Singleton<NotFullNotEmptyState>::instance(); }
};

//m)implement FullState
class FullState :public StackState
{
	friend class Singleton<FullState>;
public:
	void Push(int element, Stack* stk) override { throw std::string("Cannot Push data to Full Stack\n"); }
	int Pop(Stack* stk) override;
	void State() { std::cout << "Full State\n"; }
	static FullState* Instance() { return Singleton<FullState>::instance(); }
};



#endif
