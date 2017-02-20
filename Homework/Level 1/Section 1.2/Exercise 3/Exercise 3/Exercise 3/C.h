#ifndef C_H
#define C_H
#include<vector>
#include<iostream>
class C {
private:
	std::vector<double> m_data;
public:
	C(const C & source);
    C();
	C(double input);
	C(double data, int size);
	C(const std::vector<double>& source);
	C(C&& source);
	~C();
	C& operator=(const C & source);
	C& operator=(C&& source);
	void print() const;
	void scale(double scalor);
	int getdatasize() const;
	void moveOps(C&& source);
};
#endif