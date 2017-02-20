#include "C.h"
#include<iostream>
#include<algorithm>
#include<iterator>
C::C(double input) noexcept {
	m_data.push_back(input);
	std::cout << "specific constructor\n";
}
C::C(double input, int size) noexcept {
	for (int i = 0; i < size; i++) m_data.push_back(input);
	std::cout << "another specific constructor\n";
}
/*C::C() { 
m_data.push_back(1.1);
std::cout << "default constructor\n";
}*/
/*C::C(const C & source) :m_data(source.m_data) {
	std::cout << "copy constructor is called\n";
}
C& C::operator=(const C & source) {
	m_data = source.m_data;
	std::cout << "assignment operator is called\n";
	return *this;
}*/
C::~C() {
	std::cout << "destructor is called\n";
}
void C::print() const noexcept {
	std::for_each(m_data.begin(), m_data.end(), [](double input) {std::cout << input << std::endl; });
}
void C::scale(double scalor) {
	for (auto it = m_data.begin(); it < m_data.end(); it++) *it *= scalor;
}
int C::getdatasize() const {
	return m_data.size();
}
C & trial(const C & source) {
	C c2;
	//c2 = source; error using deleted function
	//C c3(source); error using deleted function
	return c2;
}
