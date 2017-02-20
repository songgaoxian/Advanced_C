#include "C.h"
#include<iostream>
#include<algorithm>
#include<iterator>
#include<vector>
C::C(double input) {
	m_data.push_back(input);
	std::cout << "specific constructor\n";
}
C::C(double input, int size) {
	for (int i = 0; i < size; i++) m_data.push_back(input);
	std::cout << "another specific constructor\n";
}
C::C() {
m_data.push_back(1.1);
std::cout << "default constructor\n";
}
C::C(const C & source) :m_data(source.m_data) {
std::cout << "copy constructor is called\n";
}
C::C(const std::vector<double>& source) : m_data(source) {
	std::cout << "constructor with vector is called\n";
}
C::C(C&& source) {
	std::cout << "move constructor is called\n"; //identify which constructor is called
	m_data = std::move(source.m_data);
}
C& C::operator=(const C & source) {
m_data = source.m_data;
std::cout << "assignment operator is called\n";
return *this;
}
C& C::operator=(C&& source) {
	std::cout << "move assignment operator is called\n";//identify which assignment operator is called
	m_data = std::move(source.m_data);
	return *this;
}
C::~C() {
	std::cout << "destructor is called\n";
}
void C::print() const {
	std::for_each(m_data.begin(), m_data.end(), [](double input) {std::cout << input << std::endl; });
}
void C::scale(double scalor) {
	for (auto it = m_data.begin(); it < m_data.end(); it++) *it *= scalor;
}
int C::getdatasize() const {
	return m_data.size();
}
void C::moveOps(C&& source) {
	m_data = std::move(source.m_data);
}

