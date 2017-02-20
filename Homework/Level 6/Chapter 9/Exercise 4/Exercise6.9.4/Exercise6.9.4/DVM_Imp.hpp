//DVM_Imp.hpp
//derived classes from DVM_Interface

#ifndef DVM_Imp_HPP
#define DVM_Imp_HPP

#include"DVM_Interface.hpp"
#include<map>

using Product = std::tuple<int, int>;//tuple<price,quantity>

class Source :public ISource
{
public:
	virtual std::string message();
};
class Auth : public IAuth
{
private:
	int money;
public:
	Auth() { money = 0; }
	virtual int amount();
	virtual void increment(int amount);
	virtual void decrement(int amount);
};
class Resource :public IResource
{
private:
	std::map<std::string, Product> drinks;
public:
	Resource();//constructor
	virtual void displayProducts();
	virtual Product getProduct(std::string name);
	virtual void updateProduct(std::string name, int quantity);
};
class Sink : public ISink
{
public:
	virtual void notify(std::string prod, bool status);
};
class MIS : public IMIS
{
private:
	bool inprocess;
	bool complete;
public:
	MIS();
	virtual void notify();
};
//DVM class
class DVM : private Source, private Auth, private Resource, private Sink, private MIS
{
private:
	Source iso_;
	Auth ia_;
	Resource ir_;
	Sink isi_;
	MIS im_;
public:
	//contructor
	DVM(Source& iso, Auth& ia, Resource& ir, Sink& isi, MIS& im);
	void run();
};

#endif