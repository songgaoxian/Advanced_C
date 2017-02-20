#include "Proposition.h"
#include<iostream>

int main() {
	//b) test
	//default proposition
	Proposition p1;
    //construct with bool
	Proposition p2(true);
	std::cout << "p1 represents " << std::boolalpha << p1.Getdata() << std::endl;
	std::cout << "p2 represents " << std::boolalpha << p2.Getdata() << std::endl;
	//test operators
	std::cout << "is p1==p2? " << std::boolalpha << (p1 == p2).Getdata() << std::endl;
	std::cout << "is p1!=p2? " << std::boolalpha << (p1 != p2).Getdata() << std::endl;
	std::cout << "p1 and p2 " << std::boolalpha << (p1&p2).Getdata() << std::endl;
	std::cout << "p1 or p2 " << std::boolalpha << (p1 | p2).Getdata() << std::endl;
	std::cout << "p1 XOR p2 " << std::boolalpha << (p1^p2).Getdata() << std::endl;
	std::cout << "p1->p2 " << std::boolalpha << (p1%p2).Getdata() << std::endl;
	std::cout << "p1<->p2 " << std::boolalpha << bicondition(p1, p2).Getdata() << std::endl;
	std::cout << "!p1 " << std::boolalpha << (!p1).Getdata() << std::endl;
	std::cout << "true=p1 " << std::boolalpha << p1.assign(true).Getdata() << std::endl;

	//check that my code satisfy DeMorgan's Law
	std::cout << "Does p1 and p2 satisfy DeMorgan's law?\n";
	std::cout << std::boolalpha << ((!(p1 | p2)) == ((!p1)&(!p2))).Getdata() << std::endl;
	std::cout << std::boolalpha << (!(p1&p2) == ((!p1) | (!p2))).Getdata() << std::endl;
	std::cout << "Does p1 and p1 satisfy DeMorgan's law?\n";
	std::cout << std::boolalpha << ((!(p1 | p1)) == ((!p1)&(!p1))).Getdata() << std::endl;
	std::cout << std::boolalpha << (!(p1&p1) == ((!p1) | (!p1))).Getdata() << std::endl;
	std::cout << "Does p2 and p2 satisfy DeMorgan's law?\n";
	std::cout << std::boolalpha << ((!(p2 | p2)) == ((!p2)&(!p2))).Getdata() << std::endl;
	std::cout << std::boolalpha << (!(p2&p2) == ((!p2) | (!p2))).Getdata() << std::endl;
	//check that my code satisfy distributive law
	std::cout << std::endl;
	std::cout << "Does p1,p1 and p1 satisfy distributive laws?\n";
	std::cout << std::boolalpha << ((p1&(p1 | p1)) == ((p1&p1) | (p1 | p1))).Getdata() << std::endl;
	std::cout << std::boolalpha << ((p1 | (p1&p1)) == ((p1 | p1)&(p1 | p1))).Getdata() << std::endl;
	std::cout << "Does p1,p2 and p1 satisfy distributive laws?\n";
	std::cout << std::boolalpha << ((p1&(p2 | p1)) == ((p1&p2) | (p1 | p1))).Getdata() << std::endl;
	std::cout << std::boolalpha << ((p1 | (p2&p1)) == ((p1 | p2)&(p1 | p1))).Getdata() << std::endl;
	std::cout << "Does p2,p2 and p2 satisfy distributive laws?\n";
	std::cout << std::boolalpha << ((p2&(p2 | p2)) == ((p2&p2) | (p2 | p2))).Getdata() << std::endl;
	std::cout << std::boolalpha << ((p2 | (p2&p2)) == ((p2 | p2)&(p2 | p2))).Getdata() << std::endl;
	std::cout << "Does p2,p1 and p2 satisfy distributive laws?\n";
	std::cout << std::boolalpha << ((p2&(p1 | p2)) == ((p2&p1) | (p2 | p2))).Getdata() << std::endl;
	std::cout << std::boolalpha << ((p2 | (p1&p2)) == ((p2 | p1)&(p2 | p2))).Getdata() << std::endl;
	std::cout << "Does p2,p2 and p1 satisfy distributive laws?\n";
	std::cout << std::boolalpha << ((p2&(p2 | p1)) == ((p2&p2) | (p2 | p1))).Getdata() << std::endl;
	std::cout << std::boolalpha << ((p2 | (p2&p1)) == ((p2 | p2)&(p2 | p1))).Getdata() << std::endl;

	//check[A->(B->C)]<->[(A&B)->C]
	std::cout << std::endl;
	std::cout << "check statement [A->(B->C)]<->[(A&B)->C]\n";
	std::cout << "Does p1, p1 and p1 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p1 % (p1%p1), (p1&p1) % p1).Getdata() << std::endl;
	std::cout << "Does p2, p1 and p1 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p2 % (p1%p1), (p2&p1) % p1).Getdata() << std::endl;
	std::cout << "Does p1, p2 and p1 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p1 % (p2%p1), (p1&p2) % p1).Getdata() << std::endl;
	std::cout << "Does p1, p1 and p2 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p1 % (p1%p2), (p1&p1) % p2).Getdata() << std::endl;
	std::cout << "Does p2, p2 and p2 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p2 % (p2%p2), (p2&p2) % p2).Getdata() << std::endl;
	std::cout << "Does p1, p2 and p2 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p1 % (p2%p2), (p1&p2) % p2).Getdata() << std::endl;
	std::cout << "Does p2, p1 and p2 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p2 % (p1%p2), (p2&p1) % p2).Getdata() << std::endl;
	std::cout << "Does p2, p2 and p1 satisfy the statement?\n";
	std::cout << std::boolalpha << bicondition(p2 % (p2%p1), (p2&p2) % p1).Getdata() << std::endl;



	return 0;
}