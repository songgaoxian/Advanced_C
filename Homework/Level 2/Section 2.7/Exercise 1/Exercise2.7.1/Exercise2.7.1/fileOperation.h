#ifndef FileOperation_H
#define FileOperation_H
#include<iostream>
#include<fstream>
#include<system_error>
#include<boost/system/system_error.hpp>
#include<boost/system/error_code.hpp>
#include<string>

//a) boost version
//this function is to open a file, print record and close it
boost::system::error_condition fileOperation(std::string flocator) {
	//for b)
	//check if file exists
	if (std::ifstream(flocator).good()) {
		std::cout << "file exists\n";
	}
	else {
		return boost::system::errc::make_error_condition(boost::system::errc::no_such_file_or_directory);
	}
	//end of b)
	errno = 0;
	std::ifstream fileToRead;
	//open the specified file
	fileToRead.open(flocator, std::ifstream::in);
	//print the content
	std::cout << (char)fileToRead.get();
	//continue printing content until end
	while (fileToRead.good()) {
		std::cout << (char)fileToRead.get();
	}
	//close file
	fileToRead.close();
	//get error_code
	boost::system::error_code ec(errno, boost::system::generic_category());
	return boost::system::error_condition(errno, boost::system::generic_category());
}

//d)c++ version
//this function is to open a file, print record and close it
std::error_condition fileOperationC(std::string flocator) {
	//for b)
	//check if file exists
	if (std::ifstream(flocator).good()) {
		std::cout << "file exists\n";
	}
	else {
		return std::make_error_condition(std::errc::no_such_file_or_directory);
	}
	//end of b)
	errno = 0;
	std::ifstream fileToRead;
	//open the specified file
	fileToRead.open(flocator, std::ifstream::in);
	//print the content
	std::cout << (char)fileToRead.get();
	//continue printing content until end
	while (fileToRead.good()) {
		std::cout << (char)fileToRead.get();
	}
	//close file
	fileToRead.close();
	//get error_code
	std::error_code ec(errno, std::generic_category());
	return std::error_condition(errno, std::generic_category());
}
#endif
