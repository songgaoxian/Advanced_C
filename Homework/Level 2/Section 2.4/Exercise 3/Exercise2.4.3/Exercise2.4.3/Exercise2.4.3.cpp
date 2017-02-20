#include<memory>
#include<iostream>
using std::cout;
using std::auto_ptr;

int main() {
	//a)
	//Define auto_ptr
	std::auto_ptr<double> d(new double(1.0));

	//dereference
	*d = 2.0;

	//change ownership fo auto_ptr
	//then d is undefined
	auto_ptr<double> d2 = d;
	*d2 = 3.0;

	//cout << "Auto values: " << *d.get() << "," << *d2.get(); //it cannot run properly
	cout << *d2.get()<<std::endl; // it can run properly
	//end of a)

	//for b)
	//define unique pointer
	std::unique_ptr<double> sd(new double(1.0));
	//dereference
	*sd = 2.0;
	//change ownership
	//std::unique_ptr<double> sd2 = sd; //cannot compile
	std::unique_ptr<double> sd2 = std::move(sd); //can compile
	*sd2 = 3.0;

	//cout << "Auto values: " << *sd.get() << ", " << *sd2.get();//cannot run properly
	cout << *sd2.get() << std::endl; //can run properly
	//end of b)
	return 0;
}