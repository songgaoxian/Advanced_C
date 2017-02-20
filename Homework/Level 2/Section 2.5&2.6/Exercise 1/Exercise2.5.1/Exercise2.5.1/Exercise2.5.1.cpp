#include<numeric>
#include<climits>
#include<iostream>
#include<string>
#include<math.h>

//for a)
//this function classify input t
template<typename T>
const char* Classify(T t) {
	//return corresponding string based on t's classficiation
	switch (std::fpclassify(t)) {
	case FP_INFINITE: return "Inf";
	case FP_NAN: return "NaN";
	case FP_NORMAL: return "normal";
	case FP_SUBNORMAL:return "subnormal";
	case FP_ZERO: return "zero";
	default: return "unknown";
	}
}

//for b)
//this function is to apply isfinite, isinf, isnan and isnormal
template<typename T>
void Check(T t) {
	std::cout << "Is finite? " << std::boolalpha<<std::isfinite<T>(t) << std::endl;
	std::cout << "Is infinite? " <<std::boolalpha<< std::isinf<T>(t) << std::endl;
	std::cout << "Is nan? " <<std::boolalpha<< std::isnan<T>(t) << std::endl;
	std::cout << "Is normal? " <<std::boolalpha<<std::isnormal<T>(t) << std::endl;
}

int main() {
	//variables are created for testing in a)
	double val = std::numeric_limits<double>::max();
	double val2 = std::numeric_limits<double>::min() - 3.1415;
	//test val and values derived from val and print result
	std::cout << "val is " << Classify(val) << ", 2.0*val is " << Classify(2.0*val) << ", 3.1415+val is " << Classify(3.1415 + val) << std::endl;
   //test val2, val2/2.0 and DBL_MIN/2
	std::cout << "val2 is " << Classify(val2) << ", val2/2.0 is " << Classify(val2 / 2.0) << ", DBL_MIN/2 is " << Classify(DBL_MIN / 2) << std::endl;
	//end of a)

	//check the following variables for b)
	double factor = 2.0;
	std::cout << "check factor:\n";
	//check factor
	Check(factor);
	
	val = factor*std::numeric_limits<double>::max();
	std::cout << "\ncheck val as factor*max:\n";
	//check val
	Check(val);

	val = -val;
	std::cout << "\ncheck val as -val:\n";
	//check val
	Check(val);

	std::cout << "\ncheck sqrt(-1):\n";
	//check sqrt(-1)
	Check(std::sqrt(-1.0));

	std::cout << "\ncheck log(0.0):\n";
	//check log(0.0)
	Check(std::log(0.0));

	std::cout << "\ncheck exp(val):\n";
	//check exp(val)
	Check(exp(val));
	//end of b)

	return 0;


}