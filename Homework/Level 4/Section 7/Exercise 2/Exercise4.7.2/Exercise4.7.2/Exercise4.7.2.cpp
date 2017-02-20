//Exercise4.7.2
//
//use bimap with tag
//written on 2016/6/21

#include<iostream>
#include<boost/bimap.hpp>
#include<boost/bimap/unordered_set_of.hpp>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/string_generator.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<string>
#include<boost/lexical_cast.hpp>

struct IpAddress{};
struct DomainName{};
//a)create a bimap called DNS
using DNS = boost::bimap<boost::bimaps::unordered_set_of<boost::bimaps::tagged<boost::uuids::uuid, IpAddress>>, 
	                     boost::bimaps::unordered_set_of<boost::bimaps::tagged<std::string, DomainName>>>;

//c)print DNS
void print(DNS dns) {
	for (auto it = dns.begin(); it != dns.end(); it++) {
		boost::uuids::uuid uip = it->get<IpAddress>();
		//get the string version of ip address
		std::string ip = boost::lexical_cast<std::string>(uip);
		//get domain name
		std::string domain = it->get<DomainName>();
		//print dns
		std::cout << ip << " is associated with " << domain << '\n';
	}
}

int main() {
	//b)create instance of DNS
	DNS myDNS;
	//create uuid string generator
	boost::uuids::string_generator gen;
	//create ip addresses
	boost::uuids::uuid ip1 = gen(std::string("01001101010001110100001111111111"));
	boost::uuids::uuid ip2 = gen(std::string("11000111000001110100001110011101"));
	boost::uuids::uuid ip3 = gen(std::string("01011111000101010101100110010100"));
	//create domain names
	std::string doname1 = "www.hello.com";
	std::string doname2 = "www.world.com";
	std::string doname3 = "www.flyfly.org";
	//insert domain names and ip addresses to DNS
	using Pair = DNS::value_type;
	myDNS.insert(Pair(ip1, doname1));
	myDNS.insert(Pair(ip2, doname2));
	myDNS.insert(Pair(ip3, doname3));
	
	//find domain name based on ip address
	auto iter = myDNS.by<IpAddress>().find(ip1);
	if (iter != myDNS.by<IpAddress>().end()) {
		//convert ip1 to string
		std::string sip=boost::lexical_cast<std::string>(ip1);
		//get the found domain name
		std::string sDoname = iter->get<DomainName>();
		std::cout << sip << " is associated with " << sDoname << '\n';
	}
	
	//find ip address based on domain name
	auto it = myDNS.by<DomainName>().find(doname1);
	if (it != myDNS.by<DomainName>().end()) {
		//get the found ip address
		boost::uuids::uuid buid = it->get<IpAddress>();
		//convert to string
		std::string sip = boost::lexical_cast<std::string>(buid);
		std::cout << doname1 << " is associated with " << sip << '\n';
	}

	//call print
	print(myDNS);

	return 0;
}
