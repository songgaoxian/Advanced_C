#include<boost/asio.hpp>
#include<string>
#include<iostream>

int main() {
	boost::asio::ip::address_v4 ipAdd(boost::asio::ip::address_v4::from_string("127.0.0.1"));
	int port = 80; //http
	//a)create an endpoint based IP address and port number
	boost::asio::ip::udp::endpoint endPt(ipAdd, port);
	//b)print out endpoint
	std::cout << endPt << '\n';
	std::cout << "Address: " << endPt.address().to_string() << " Port: " << endPt.port() << "\n";
	//c)Get the protocol
	auto protocol = endPt.protocol();
	std::cout << "protocol type: " << protocol.type() << '\n';
	return 0;
}