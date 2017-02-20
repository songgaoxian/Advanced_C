//Exercise4.1.3
//
//exercise to split and join strings
//written on 2016/6/18

#include<string>
#include<iostream>
#include<boost/algorithm/string.hpp>
#include<vector>
#include<boost/date_time/gregorian/gregorian.hpp>
#include<map>

//b)
boost::gregorian::date convert_to_date(std::string& s) {
	//store the splited result of string s
	std::vector<std::string> split_string;
	//split s
	boost::algorithm::split(split_string, s, boost::algorithm::is_any_of("-"));
	//get year, month and day from split_string
	int year = boost::lexical_cast<int>(split_string[0]);
	int month = boost::lexical_cast<int>(split_string[1]);
	int day = boost::lexical_cast<int>(split_string[2]);
	//return the converted date
	return boost::gregorian::date(year, month, day);
}

//c)
std::map<std::string, double> convert_to_map(std::string& s) {
	//record the splited s
	std::vector<std::string> split_string;
	//split s
	boost::algorithm::split(split_string, s, boost::algorithm::is_any_of("="));
	//convert value to num
	double num = boost::lexical_cast<double>(split_string[1]);
	std::map<std::string, double> smap;
	//set value
	smap[split_string[0]] = num;
	return smap;
}


int main() {
	//a)
	std::cout << "a)\n";
	std::string sA("1,2,3,4/5/9*56");
	std::cout << "sA=" << sA << '\n';
	//store splited string
	std::vector<std::string> result;
	//split string sA
	boost::algorithm::split(result, sA, boost::algorithm::is_any_of(",/*"));
	//print out splited sA
	std::cout << "after split:";
	for (int i = 0; i < result.size(); ++i) {
		std::cout << result[i]<<' ';
	}
	//join result
	sA=boost::algorithm::join(result, "/");
	std::cout << "\nafter join:" << sA << '\n';

	//b)
	std::cout << "\nb)\n";
	std::string sB("2015-12-31");
	//convert to date
	boost::gregorian::date d = convert_to_date(sB);
	//print d
	std::cout << "converted to date:" << d << '\n';

	//c)
	std::cout << "\nc)\n";
	//create sC
	std::string sC("value=34.4");
    //convert to map
	std::map<std::string, double> m = convert_to_map(sC);
	//print m
	std::cout << "converted to map:\n";
	for (auto it = m.begin(); it != m.end(); it++)
		std::cout << "Key:" << it->first << "; Value:" << it->second;
	std::cout << '\n';
	return 0;
	
}
