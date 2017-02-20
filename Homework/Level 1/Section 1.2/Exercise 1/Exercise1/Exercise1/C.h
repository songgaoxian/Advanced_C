#ifndef C_H
#define C_H
#include<vector>
#include<iostream>
class C {
private:
	std::vector<double> m_data;
	C(const C & source)=delete; 
	C& operator=(const C & source)=delete;
public:
	explicit C()=default; 
	explicit C(double input) noexcept;
	explicit C(double data, int size) noexcept;
	constexpr explicit C(const std::vector<double>& source) :m_data(source) {} 
	~C();
	void print() const noexcept;
	void scale(double scalor);
    int getdatasize() const;
	friend C & trial(const C & source);
};
#endif