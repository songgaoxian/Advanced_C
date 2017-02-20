#ifndef Point_H
#define Point_H
#include<iostream>
#include<string>
using std::cout;
class Point {
private:
	double x, y;
public:
	Point(double srcx, double srcy) :x(srcx), y(srcy) { cout << "create a point\n"; }
	virtual ~Point() { cout << "point destructor\n"; }
	std::string ToString() const {
		return std::string("(" + std::to_string(x) + "," + std::to_string(y) + ")");
	}
};
std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << p.ToString();
	return os;
}
#endif
