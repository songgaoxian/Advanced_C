//Exercise4.2.8
//
//apply regex syntax to process data.txt
//written on 2016/6/19

#include<regex>
#include<string>
#include<iostream>
#include<vector>
#include<list>
#include<tuple>
#include<boost/date_time/gregorian/gregorian.hpp>
#include<boost/lexical_cast.hpp>

using Data = std::tuple<boost::gregorian::date, std::vector<double>>;
using ResultSet = std::list<Data>;

int main() {
	FILE* f;
	//store header info
	char header[300];
	std::string sheader;

	//store data line info
	char line[300];
	std::string sline;

	//store market data
	std::vector<double> market_data;

	//store date info
	boost::gregorian::date date;
	//store Data of one line
	Data dat;
	//store all dat in result
	ResultSet result;

	f = fopen("data.txt", "r");
	if (f!= NULL) {
		fgets(header, 300, f);
		sheader = header;

		//declare variables to be used in loop
		std::regex rg(",");
		std::regex rg1("[0-9]{4}-[0-9]{2}-[0-9]{2}");
		std::regex rg2("-");
		std::regex rg3("[0-9]+(.[0-9]+)?");
		std::sregex_token_iterator itEnd;
		std::sregex_token_iterator itRg;
		std::sregex_token_iterator itRg2;
		std::string tempDate;
		std::string tempS;
		double marketData;
		//read all data lines in data.txt
		while (!feof(f)) {
			//read one line
			if (fgets(line, 300, f) == NULL) break;
			sline = line;

			//split sline using sregex_token_iterator
			itRg=std::sregex_token_iterator(sline.begin(), sline.end(), rg, -1);
			
			//get Date
			tempDate = *itRg;
			//remove blanks
			std::sregex_token_iterator dateIter(tempDate.begin(), tempDate.end(), rg1, 0);
			tempDate = *dateIter;
			
			//split tempDate to get year, month, day
			itRg2= std::sregex_token_iterator(tempDate.begin(), tempDate.end(), rg2, -1);
			
			//get year string
			std::string syear = *itRg2;
			//convert to int
			int year = boost::lexical_cast<int>(syear);

			//get month string
			itRg2++;
			std::string smonth = *itRg2;
			//convert to int
			int month = boost::lexical_cast<int>(smonth);

			//get day string
			itRg2++;
			std::string sday = *itRg2;
			int day = boost::lexical_cast<int>(sday);

			//get date
			date = boost::gregorian::date(year, month, day);

			itRg++;
			//get market data info
			for (auto it = itRg; it != itEnd; ++it) {
				//get string of market data
				tempS = *it;
				//get only valid numbers (trim newline or blanks)
				std::sregex_token_iterator stIt(tempS.begin(), tempS.end(), rg3, 0);
				tempS = *stIt;
				//convert to double
				marketData = boost::lexical_cast<double>(tempS);
				//push to market_data
				market_data.push_back(marketData);
			}
			//get Data of the line
			dat = std::make_tuple(date, market_data);

			//store dat in result
			result.push_back(dat);

			//clear market_data
			market_data.clear();
		}	
	}

	//print out result
	std::cout << sheader;
	for (auto it = result.begin(); it != result.end(); it++) {
		dat = *it;
		//print out date
		std::cout << std::get<0>(dat) << ":";
		//get market_data info
		market_data = std::get<1>(dat);
		for (auto iter = market_data.begin(); iter != market_data.end(); iter++)
			std::cout << *iter << ",";
		std::cout << '\n';
	}

	return 0;
}