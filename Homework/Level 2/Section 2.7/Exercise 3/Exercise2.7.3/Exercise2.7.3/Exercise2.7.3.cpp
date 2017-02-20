#include<iostream>
#include<system_error>
#include<condition_variable>
#include<string>

int main() {
	//a)create error conditions based on POSIX error codes
	std::error_condition err1(std::errc::io_error);
	std::error_condition err2(std::errc::network_unreachable);
	std::error_condition err3(std::errc::no_such_file_or_directory);
	std::error_condition err4(std::errc::not_a_socket);
	std::error_condition err5(std::errc::permission_denied);
	//end of a)

	//b) create error condition based on value 128 and generic category
	int val = 128;
	std::error_condition err6(val, std::generic_category());
	//end of b)

	//c)create error condition with make_condition
	std::error_condition err7 = std::make_error_condition(std::io_errc::stream);
	//end of c)

	//display all messages of created error conditions
	std::cout << err1.message() << std::endl;
	std::cout << err2.message() << std::endl;
	std::cout << err3.message() << std::endl;
	std::cout << err4.message() << std::endl;
	std::cout << err5.message() << std::endl;
	std::cout << err6.message() << std::endl;
	std::cout << err7.message() << std::endl;
	return 0;
}