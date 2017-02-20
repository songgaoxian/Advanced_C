//Origin.cpp
//implement classes in Origin.hpp

#include"Origin.hpp"

std::vector<std::string> MyInput::message() const {
	FILE* pfile;
	//specify file to be read
	pfile = fopen("old.txt", "r");
	//store each record temporarily
	std::string line;
	const int max = 10000;
	char* readline = new char[max];
	//store all records
	std::vector<std::string> result;
	while (fgets(readline, max, pfile) != nullptr) {
		line = std::string(readline);
		//push record to vector
		result.push_back(line);
	}
	delete readline;
	return result;
}

void MyConverter::convert(std::vector<std::string>& s) const {
	for (auto it = s.begin(); it != s.end(); ++it) {
		boost::trim(*it);
		boost::to_upper(*it);
	}
	std::cout << "end of converter\n";
}

void MyOutput::print(std::vector<std::string>& s) const {
	FILE* pfile;
	pfile = fopen("new.txt", "w");
	for (auto it = s.begin(); it != s.end(); ++it) {
		fputs((*it).c_str(), pfile);
		fputc('\n', pfile);
	}
	std::cout << "strings are copied to new.txt\n";
}

void MyOutput::end() const { std::cout << "end\n"; }