//Origin.hpp
//copy original codes in 9.3.4

#ifndef Origin_HPP
#define Origin_HPP

#include<string>
#include<iostream>
#include<boost/algorithm/string.hpp>
#include<vector>

template<typename I, typename O,typename Processing>
class SUD_O : private I, private O, private Processing
{
private:
	using I::message;
	using Processing::convert;
	using O::print;
	using O::end;
public:
	void run() { auto s = message(); convert(s); print(s); end(); }
};

class MyInput
{
public:
	std::vector<std::string> message() const;
};

class MyConverter
{
public:
	void convert(std::vector<std::string>& s) const;
};

class MyOutput
{
public:
	void print(std::vector<std::string>& s) const;
	void end() const;
};



#endif