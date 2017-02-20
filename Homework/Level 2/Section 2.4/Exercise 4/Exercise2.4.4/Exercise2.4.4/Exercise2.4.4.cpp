#include"Class.h"
#include<list>
#include<memory>

//b) create instances and Derived
Base& createDerived() {
	return Derived();
}

int main() {
	//a) create a list of smart pointers to Base
	std::list<std::shared_ptr<Base>> blist;
	
	//b)
	//add Derived instances to blist
	std::shared_ptr<Base> shptr;
	for (int i = 0; i < 3; ++i) {
		*shptr = createDerived();
		blist.push_back(shptr);
	}
	//c)
	//base and derived destructors are called three times before go to an inner scope
	//memory is managed dynamically and properly
	cout << "go to an inner scope\n";
	{
		//b) use a different list
		std::list<std::shared_ptr<Base>> blist1;
		for (int i = 0; i < 2; ++i) {
			*shptr = createDerived();
			blist1.push_back(shptr);
		}
	}
	//before the next statement, base and derived destructors are called twice
	//memory is managed dynamically and properly
	cout << "go out of the inner scope\n";
	return 0;
}