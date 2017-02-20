#include<iostream>
#include<system_error>
#include<fstream>
#include<string>

int main() {
	//a
	//create file with non-existing file
	std::fstream file(std::string("DOESNOTEXIST.txt"));
	try {
		//set the exception mask of the file stream
		file.exceptions(file.failbit | file.badbit);
	}
	catch (const std::ios_base::failure& e) {
		//a) use e.code() and compare with io_errc::stream
		std::cout << "is e.code() same as io_errc::stream?\n";
		std::cout << std::boolalpha << (e.code() == std::io_errc::stream) << std::endl;
		//end of a)

		//b)
		if (e.code() == std::io_errc::stream) {
			//if true
			//create error code with e.code()
			std::error_code ec1(e.code());
			//create error condition with ec1
			std::error_condition ec2(ec1.value(),std::generic_category());
			//print properties of ec2
			std::cout << "ec2 info:\n";
			std::cout << "value=" << ec2.value() << "; category=" << ec2.category().name() << std::endl;
			std::cout << "message: " << ec2.message() << std::endl;
		}
	}
	catch (...) {
		std::cout << "catch all\n";
	}

	return 0;

}