//Exception.h
//
//create classes Exception, NoFundsException and NoAccessException
//written on 2016/6/30

#ifndef Exception_H
#define Exception_H
#include<string>
#include<iostream>
//a)base class
class Exception{};
//b)
class NoFundsException :public Exception
{
public:
	NoFundsException() { std::cout << "Not enough fund\n"; }
};
//c)
class NoAccessException :public Exception
{
public:
	NoAccessException() { std::cout << "Not permitted access\n"; }
};


#endif
