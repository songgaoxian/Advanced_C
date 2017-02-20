#include"fileOperation.h"

int main() {
	//c)
	//test with an existing file
	std::cout << "\ntest an existing file\n";
	boost::system::error_condition err = fileOperation("me.txt");
	std::cout << err.message() << std::endl;
	//test a non-existing file
	std::cout << "\ntest an non-existing file\n";
	boost::system::error_condition err1=fileOperation("me1.txt");
	std::cout << err1.message() << std::endl;
	//end of c)

	//d)test c++ version
	//test with an existing file
	std::cout << "\ntest an existing file\n";
	std::error_condition err3 = fileOperationC("me.txt");
	std::cout << err3.message() << std::endl;
	//test a non-existing file
	std::cout << "\ntest an non-existing file\n";
	std::error_condition err4 = fileOperationC("me1.txt");
	std::cout << err4.message() << std::endl;
	//end of d)

	return 0;
}