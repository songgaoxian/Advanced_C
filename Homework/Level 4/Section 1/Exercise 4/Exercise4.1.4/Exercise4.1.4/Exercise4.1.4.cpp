//Exercise4.1.4
//
//apply string algo to process data.txt and print out contents
//written on 2016/6/18

#include<boost/algorithm/string.hpp>
#include<boost/date_time/gregorian/gregorian.hpp>
#include<tuple>
#include<vector>
#include<list>
//copied
using Data = std::tuple<boost::gregorian::date, std::vector<double>>;
using ResultSet = std::list<Data>;
//copied from 4.1.3
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


int main() {
	FILE* pFile;
	//store the line of a file
	char line[300];
	std::string sline;
	std::string header;
	//store market data
	std::vector<double> market_data;
	//store date
	boost::gregorian::date day;
	//Data to store one line of info
	Data dat;
	//the list to store all data
	std::list<Data> lst;
	//store splited line
	std::vector<std::string> split_string;

	//open the file containing data
	pFile = fopen("data.txt", "r");
	//check if file can be opened
	if (pFile == NULL) {
		std::cout << "error opening file\n";
	}
	else {
		//read the header
		fgets(line, 300, pFile);
		header = line;
		//while file not reach end of file
		while (!feof(pFile)) {
			//read the line of file
			if(fgets(line, 300, pFile)==NULL) break;
			//store the line as a string
			sline = line;
			//split the string
			boost::algorithm::split(split_string, sline, boost::algorithm::is_any_of(","));
			//trim blanks
			for (auto it = split_string.begin(); it != split_string.end(); it++) {
				boost::algorithm::trim(*it);
				boost::algorithm::trim_right(*it);
			}
			//get day
			day = convert_to_date(split_string[0]);
			//get market data
			for (auto it = split_string.begin() + 1; it != split_string.end(); ++it) {
				//convert string to data
				double temp_dat = boost::lexical_cast<double>(*it);
				//store data in market_data
				market_data.push_back(temp_dat);
			}
			//get the data of the line read
			dat = std::make_tuple(day, market_data);
			//store the info in the list
			lst.push_back(dat);
			//clear vectors for next line
			market_data.clear();
			split_string.clear();
		}
	}

	//print out the lst
	std::cout << header;
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		//get Data
		dat = *it;
		//print out data
		std::cout << std::get<0>(dat) << ",";
		//get market data
		market_data = std::get<1>(dat);
		//print out market data
		for (auto iter = market_data.begin(); iter != market_data.end(); iter++) {
			std::cout << *iter << ",";
		}
		std::cout << '\n';
	}


	return 0;
}
