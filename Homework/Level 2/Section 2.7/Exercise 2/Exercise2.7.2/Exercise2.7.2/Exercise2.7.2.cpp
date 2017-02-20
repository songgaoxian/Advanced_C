#include<iostream>
#include<system_error>
#include<tuple>
#include<string>

//b)
std::tuple<std::string, int, std::string> GetInfo(const std::error_condition& e) {
	//return info of e regarding error message, error code and error category name
	return std::make_tuple<std::string, int, std::string>(e.message(), e.value(), e.category().name());
}


int main() {
	//a) create instances of std::error_condition
	//create with default constructor
	std::error_condition errD;
	//create with error code and category
	const int errcode = 4;
	std::error_condition errCC(errcode, std::generic_category());
	//create with std::errc code
	std::errc code = std::errc::bad_address;
	std::error_condition errCode(code);
	//end of a)

	//b test GetInfo
	std::string message, name;
	int codenum;
	//test errD
	//tie tuple of info to message, code and name
	std::tie(message, codenum, name) = GetInfo(errD);
	//display info
	std::cout << "errD: code=" << codenum << "; name=" << name << ";\nmessage: " << message << std::endl;

	//test errCC
	//tie tuple of info to message, code and name
	std::tie(message, codenum, name) = GetInfo(errCC);
	//display info
	std::cout << "errCC: code=" << codenum << "; name=" << name << ";\nmessage: " << message << std::endl;

	//test errCode
	//tie tuple of info to message, code and name
	std::tie(message, codenum, name) = GetInfo(errCode);
	//display info
	std::cout << "errCode: code=" << codenum << "; name=" << name << ";\nmessage: " << message << std::endl;
	//end of b)

	return 0;
}