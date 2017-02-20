#include<boost/asio/ip/address.hpp>
#include<iostream>

//determine the class of ip address
char CheckClass(boost::asio::ip::address_v4& ipa) {
	//return corresponding class name
	if (ipa.is_class_a()) return 'A';
	if (ipa.is_class_b()) return 'B';
	if (ipa.is_class_c())  return 'C';
	return 'D';
}

int main() {
	//a)create ip address from array
	boost::asio::ip::address_v4::bytes_type myArr;
	myArr[0] = 127; myArr[1] = 0; myArr[2] = 0; myArr[3] = 1;
	boost::asio::ip::address_v4 ipAddress1(myArr);
	//display the first address
	std::cout << "First ip address created from array: " << ipAddress1 << "\n";
	//create ip address from string
	boost::asio::ip::address_v4 ipAddress2(boost::asio::ip::address_v4::from_string("127.0.0.1"));
	//display second address
	std::cout << "Second ip address created from string: " << ipAddress2 << '\n';

	//b)create byte array from ip address
	auto arr=ipAddress2.to_bytes();
	std::cout << "byte array\n";
	for (int i = 0; i < arr.size(); ++i) {
		std::cout << int(arr[i]) << ".";
	}
	std::cout << '\n';

	//c)Get the address of the netmask of ip address
	std::cout << "Address of netmask is " << boost::asio::ip::address_v4::netmask(ipAddress1) << '\n';
	
	//d)Convert ip address to a string and an unsigned long
	std::string s = ipAddress1.to_string();
	unsigned long ipLong = ipAddress1.to_ulong();
	std::cout << "Converted string is " << s << '\n';
	std::cout << "Converted unsigned long is " << ipLong << '\n';

	//e)Determine the class of ip address
	char classType = CheckClass(ipAddress1);
	std::cout << "ipAddress1 is of class type " << classType << '\n';

	//f)determine is my computer big or little Endian
	int num = 1;
	if (*(char*)&num == 1) {
		std::cout << "Little Endian\n";
	}
	else {
		std::cout << "Big Endian\n";
	}
	return 0;

}