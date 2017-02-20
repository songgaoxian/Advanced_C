//Account.h
//
//create classes Account, RealAccount
//written on 2016/6/30

#ifndef Account_H
#define Account_H
#include<iostream>
#include"Exception.hpp"

//d)create account
class Account {
public:
	virtual void Withdraw(double amount) = 0; //can throw exception
	//e)GetBalance()
	virtual double GetBalance() = 0;
};
//f)create RealAccount
class RealAccount :public Account
{
private:
	double balance;
public:
	//constructor
	RealAccount(double val) :balance(val) {}
	void Withdraw(double amount) {
		//throw exception if not enough fund
		if (amount > balance) { throw NoFundsException(); }
		balance -= amount;
	}
	double GetBalance() { return balance; }
};
//g)create ProtectedAccount
class ProtectedAccount :public Account
{
private:
	double balance;
	std::string password;
	Account* acct;
public:
	ProtectedAccount(double val, std::string psw) :balance(val), password(psw) { acct = new RealAccount(val); }
	//h)implement Withdraw
	void Withdraw(double amount) { acct->Withdraw(amount); }
	//i)
	double GetBalance() {
		std::cout << "Give the password:\n";
		std::string s;
		std::cin >> s;
		if (password != s) { throw NoAccessException(); }
		return acct->GetBalance();
	}
};




#endif
