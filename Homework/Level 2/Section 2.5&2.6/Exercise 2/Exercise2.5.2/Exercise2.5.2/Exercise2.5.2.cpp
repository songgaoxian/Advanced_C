#include<numeric>
#include<cmath>
#include<limits>
#include<iostream>

//a)
//create a small C function to get epsilon
double Epsilon() {
	double epsilon = 1.0;
	while ((1.0 + 0.5*epsilon) != 1.0) {
		epsilon *= 0.5;
	}
	return epsilon;
}
//generalize the function to get epsilon
template<typename T>
T EpsilonG() {
	T epsilon = (T)1;
	while ((1.0 + 0.5*epsilon) != 1.0) {
		epsilon *= 0.5;
	}
	return epsilon;
}
//end of a)

int main() {
	//b)
	//get episilon from the above function
	double epi = EpsilonG<double>();
	//get episilon from the following function
	double epBench = std::numeric_limits<double>::epsilon();
    //print out values
	std::cout<< "epi=" << epi << "; epBench=" << epBench << std::endl;
	//compare two episilons
	std::cout << "is epi==epBench? " << std::boolalpha << (epi == epBench) << std::endl;
	//end of b)
	return 0;
}