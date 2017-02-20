#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include "C.h"
int main() {
	C smallC;
	smallC.print();
	C valueC(9.9);
	std::vector<double> input{ 1.2,3.3,4.4 };
	C getC(input);
	getC.print();

	//assignment operator is deleted and running it will incur error
	//smallC = trial(valueC); //trial is a friend function
	//copy constructor is deleted and running it will incur error
	//C copyC(valueC);
	

	return 0;
}