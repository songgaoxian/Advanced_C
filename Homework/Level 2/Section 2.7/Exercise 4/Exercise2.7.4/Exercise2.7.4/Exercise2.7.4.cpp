#include<system_error>
#include<iostream>
#include<tuple>
#include<string>

//b)
//this function returns info about error_code
std::tuple<std::string, int, std::string> GetInfo(const std::error_code& e) {
	return std::make_tuple<std::string, int, std::string>(e.message(), e.value(), e.category().name());
}
//end of b)

int main() {
	//a) 
	//create a default error code
	std::error_code errc1;
	//create an error code with error code value and category
	int val = 1;
	std::error_code errc2(val, std::generic_category());
	//end of a)

	//test b)'s function
	std::string message, name;
	int errcode;
	//get info about errc1
	std::tie(message, errcode, name) = GetInfo(errc1);
	//display info
	std::cout << "errc1: errcode=" << errcode << "; name=" << name << "\nmessage:" << message << std::endl;

	//get info about errc2
	std::tie(message, errcode, name) = GetInfo(errc2);
	//display info
	std::cout << "errc2: errcode=" << errcode << "; name=" << name << "\nmessage:" << message << std::endl;
	//end of testing b

	//c) test equality of default error code and default error condition
	if (errc1 == std::error_condition()) {
		std::cout << "default error code and default error condition are equivalent\n";
	}
	else {
		std::cout << "default error code and default error condition are not same\n";
	}
	//create two error conditions for comparison
	std::error_condition errcondi(val, std::generic_category());
	val += 2;
	std::error_condition errcondi2(val, std::generic_category());
	//test equality of error conditon and error code with same val
	if (errcondi == errc2) {
		std::cout << "error code and error condition are equivalent with same value\n";
	}
	if (errcondi2 != errc2) {
		std::cout << "error code and error condition are different for different values\n";
	}
	//end of c)
	return 0;

}