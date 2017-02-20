#include "Base.h"
#include<memory>
using BasePtr=std::shared_ptr < Base >;
int main() {
	Base b;
	b.draw();
	Derived d;
	d.draw();
	Derived2 d2;
	Derived d3;
	BasePtr baseptr = std::make_shared<Base>(d3);
	std::cout << "See d3 of Derived\n";
	d3.draw();
	baseptr->draw();
	return 0;
}