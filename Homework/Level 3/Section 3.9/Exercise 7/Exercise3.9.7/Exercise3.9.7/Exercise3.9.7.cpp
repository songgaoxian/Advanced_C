#include<boost/asio.hpp>
#include<array>
#include<iostream>
#include<string>

int main() {
	//a)
	//create vectors
	std::vector<char> v{'a','b','c','d'};
	//create arrays
	const int N = 4;
	std::array<char, N> arr{ 's','d','e','\0' };
	//create strings
	std::string s("never");
	//create C arrays
	char arrc[] = "hehe";
	
	std::cout << "a)\n";
	//create mutable buffers
	boost::asio::mutable_buffer mb1(&v, v.size()); //created with vector
	boost::asio::mutable_buffer mb2(&arr, arr.size());//created with array
	boost::asio::mutable_buffer mb3(&s, s.length());//created with string
	boost::asio::mutable_buffer mb4(arrc, 4);//created with c array
	std::cout << "4 mutable buffers created\n";

	//create const buffers
	boost::asio::const_buffer cb1(&v, v.size()); //created with vector
	boost::asio::const_buffer cb2(&arr, arr.size());//created with array
	boost::asio::const_buffer cb3(&s, s.length());//created with string
	boost::asio::const_buffer cb4(arrc, 4);//created with c array
	std::cout << "4 const buffers created\n";
	

	//b)
	std::cout << "b)\n";
	//give a buffers sequence
	std::vector<boost::asio::mutable_buffer> vBuffer;
	vBuffer.push_back(mb4);
	std::cout << "The copy source mb4: " << std::string(boost::asio::buffers_begin(vBuffer), boost::asio::buffers_end(vBuffer)) << '\n';
	//copy a subsection of mb4 to mb3
	mb3 = boost::asio::buffer(mb4 + 2, 2);
	vBuffer.clear();
	vBuffer.push_back(mb3);
	//display the copied result
	std::cout <<"mb3 after copy: "<<std::string(boost::asio::buffers_begin(vBuffer), boost::asio::buffers_end(vBuffer)) << '\n';
	
	//c)use buffer_cast to obtain a pointer
	unsigned char* bufferPtr = boost::asio::buffer_cast<unsigned char*>(mb4);
	std::cout <<"c)\nmb4: ";
	//print data on console
	for (int i = 0; i < 4; ++i)
		std::cout << bufferPtr[i];

	//d)copy a source buffer to a target buffer
	//target buffer
	char targetC[]="algo";
	boost::asio::mutable_buffer mb5(targetC,4);
	//copy mb4 to mb5
	boost::asio::buffer_copy(mb5, mb4);
	vBuffer.clear();
	vBuffer.push_back(mb5);
	std::cout << "\nd)\nAfter copy, mb5: ";
	std::cout << std::string(boost::asio::buffers_begin(vBuffer), boost::asio::buffers_end(vBuffer))<<'\n';

	return 0;
}