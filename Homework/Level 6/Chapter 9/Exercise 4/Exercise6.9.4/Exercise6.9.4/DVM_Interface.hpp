//DVM.hpp
//declare abstract classes related DVM

#ifndef DVM_Interface_HPP
#define DVM_Interface_HPP

#include<iostream>
#include<string>
#include<tuple>
//declare the interfaces
class ISource
{
public:
	virtual std::string message()=0;
};
class IAuth
{
public:
	virtual int amount() = 0;
	virtual void increment(int amount) = 0;
	virtual void decrement(int amount) = 0;
};
class IResource
{
public:
	virtual void displayProducts() = 0;
	virtual std::tuple<int, int> getProduct(std::string product)=0;
	virtual void updateProduct(std::string product, int quantity) = 0;
};
class ISink
{
public:
	virtual void notify(std::string prod, bool status) = 0;
};
class IMIS
{
public:
	virtual void notify() = 0;
};

#endif