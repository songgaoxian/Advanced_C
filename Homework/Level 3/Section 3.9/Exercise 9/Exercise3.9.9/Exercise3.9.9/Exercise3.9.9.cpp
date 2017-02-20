#include<boost/asio/ip/address.hpp>
#include<string>
#include<iostream>

char CheckClass(boost::asio::ip::address_v4& ipa) {
	//return corresponding class name
	if (ipa.is_class_a()) return 'A';
	if (ipa.is_class_b()) return 'B';
	if (ipa.is_class_c())  return 'C';
	return 'D';
}

int main() {
	//create an ip address
	boost::asio::ip::address_v4 ipa(boost::asio::ip::address_v4::from_string("127.0.0.1"));
	//a)determine class iAdrs
	std::cout << "a)\n";
	std::cout << ipa << ": " << "Class " << CheckClass(ipa) << '\n';

	//b)convert ipa to byte array
	boost::asio::ip::address_v4::bytes_type byte_arr = ipa.to_bytes();
	std::cout << "\nb)\n";
	//display byte_arr
	for (int i = 0; i < byte_arr.size(); ++i) {
		std::cout << int(byte_arr[i]) << '.';
	}

	//convert to string and unsigned long
	std::cout << "\nConvert ipa to string: " << ipa.to_string() << '\n';
	std::cout << "Convert ipa to unsigned long: " << ipa.to_ulong() << '\n';

	//c)Is ipa a multicast address? a loopback?
	std::cout << "\nc)\n";
	std::cout << "Is ipa a multicast address? " << std::boolalpha << ipa.is_multicast() << '\n';
	std::cout << "Is ipa a loopback? " << std::boolalpha << ipa.is_loopback() << '\n';

	//d)
	//create an address
	boost::asio::ip::address ipa2(boost::asio::ip::address::from_string("255.0.0.0"));
	//Is it a V4 or V6 address?
	std::cout << "\nd)\n";
	if (ipa2.is_v4()) std::cout << "ipa2 is a v4 address\n";
	if (ipa2.is_v6()) std::cout << "ipa2 is a v6 address\n";

	//e)
	std::cout << "\ne)\n";
	
	boost::asio::ip::address_v4::bytes_type byte_arr2;
	//initialise array to create address
	byte_arr2[0] = 74; byte_arr2[1] = 125; byte_arr2[2] = 224; byte_arr2[3] = 72;
	//create ip address from array
	boost::asio::ip::address_v4 ipa3(byte_arr2);
	std::cout << "ipa3 created from byte array: " << ipa3 << '\n';
	
	//create ip address from string
	std::string s("74.125.224.72");
	boost::asio::ip::address ipa4(boost::asio::ip::address::from_string(s));
	std::cout << "ipa4 created from byte array: " << ipa4 << '\n';

	//f)
	std::cout << "\nf)\n";
	//this array is to create ip v6
	boost::asio::ip::address_v6::bytes_type byte_arr3 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	//create ip v6 address
	boost::asio::ip::address_v6 ipa5(byte_arr3);
	std::cout << "ipa5, a ip v6 address, created from array is " << ipa5 << '\n';

	return 0;

}