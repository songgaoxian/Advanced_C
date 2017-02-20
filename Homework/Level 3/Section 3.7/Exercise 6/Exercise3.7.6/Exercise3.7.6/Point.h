#ifndef Point_H
#define Point_H
#include<cmath>

class Point {
private:
	double m_x;
	double m_y;
public:
	//constructors
	Point() {}
	Point(double x, double y) :m_x(x), m_y(y) {}
	Point(const Point& src):m_x(src.m_x),m_y(src.m_y){}
	
	//access member functions
	double X() const { return m_x; }
	double Y() const { return m_y; }
	//modifiers
	void X(double x) { m_x = x; }
	void Y(double y) { m_y = y; }
	//distance
	double Distance(const Point& src) const {
		//distance between first coordinates
		double d1 = m_x - src.m_x;
		//distance between second coordinates
		double d2 = m_y - src.m_y;
		return std::sqrt(d1*d1 + d2*d2);
	}
	//predicate to test equality
	friend bool IsEqual(const Point& p1,const Point& p2) {
		return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
	}

};
//predicate to check if within distance
bool WithinDistance(Point& centre, double thresh, const Point pt){
	return centre.Distance(pt) < thresh;
}
//comparator
struct Less {
	Less() {}
	bool operator()(const Point p1,const Point p2) {
		bool result = true;
		if (p1.X() > p2.X()) {
			result = false;
		}
		if (p1.X() < p2.X()) {
			result = true;
		}
		if (p1.X() == p2.X()) {
			result = (p1.Y() < p2.Y());
		}
		return result;
	}
};
#endif
