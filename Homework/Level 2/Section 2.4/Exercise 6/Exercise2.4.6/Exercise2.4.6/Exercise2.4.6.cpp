#include<iostream>
#include<memory>

int main() {
	//a)
	//create a shared_ptr
	std::shared_ptr<int> spint(new int(5));
	//print the shared_ptr user count (which is 1)
	std::cout << "use count of spint: " << spint.use_count() << std::endl;
	//create a weak_ptr
	std::weak_ptr<int> wkint(spint);
	//print the user count now (which is 1)
	std::cout << "use count of spint: " << spint.use_count() << std::endl;
	//end of a)

	//b)
	//assign a weak_ptr to a shared_ptr
	std::shared_ptr<int> sp2 = wkint.lock();
	//check if wkint is empty
	if (wkint.expired()) {
		std::cout << "wkint is empty\n";
	}
	else {
		std::cout << "wkint is not empty\n";
	}
	//end of b)

	//c)
	//create a shared_ptr
	std::shared_ptr<double> spd(new double(1.2));
	//create a weak_ptr
	std::weak_ptr<double> wdouble(spd);
	//print current user count
	std::cout << "for c: the initial user count is " << wdouble.use_count() << std::endl;
	
	//assign a weak_ptr to another weak_ptr
	std::weak_ptr<double> wdouble2 = wdouble;
	//print user count after assignment
	std::cout << "after assign a wek_ptr to a weak_ptr, use count is " << wdouble.use_count() << std::endl;

	//assign a weak_ptr to shared_ptr
	std::shared_ptr<double> spd2 = wdouble.lock();
	//print user count
	std::cout << "after assign a weak_ptr to a shared_ptr, use count is " << wdouble.use_count() << std::endl;
	//end of c)
	return 0;
}