//Shape.h
//
//implement Point class and Triangle class
//written on 2016/6/20

#ifndef Shape_H
#define Shape_H
#include<boost/functional/hash.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<complex>

class Point {
private:
	double m_x, m_y;
public:
	Point(double srcx,double srcy):m_x(srcx),m_y(srcy){}
	double X() const { return m_x; }
	double Y() const { return m_y; }
	friend std::size_t hash_value(const Point& pt) {
		std::size_t seed = 0;
		boost::hash_combine(seed, pt.m_x);
		boost::hash_combine(seed, pt.m_y);
		return seed;
	}
};
class Triangle {
private:
	Point m_pt1, m_pt2, m_pt3;
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3) :m_pt1(p1), m_pt2(p2), m_pt3(p3) {}
	friend std::size_t hash_value(const Triangle& trian) {
		std::size_t seed = 0;
		boost::hash_combine(seed, trian.m_pt1);
		boost::hash_combine(seed, trian.m_pt2);
		boost::hash_combine(seed, trian.m_pt3);
		return seed;
	}
};


#endif
