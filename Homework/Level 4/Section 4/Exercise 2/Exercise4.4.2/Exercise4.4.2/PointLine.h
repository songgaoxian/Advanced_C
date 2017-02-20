//PointLine.h
//
//implement Point class and LineSegment class
//written on 2016/6/20

#ifndef PointLine_H
#define PointLine_H
#include<boost/functional/hash.hpp>
#include<iostream>

class Point {
private:
	double x, y;
public:
	//constructors
	Point() :x(0), y(0) {}
	Point(double srcx, double srcy) :x(srcx), y(srcy) {}
	//a)
	//create hash for point
	friend std::size_t hash_value(const Point& src) {
		std::size_t seed = 0;
		//use hash_combine
		boost::hash_combine<double>(seed, src.x);
		boost::hash_combine<double>(seed, src.y);
		//return hash of src
		return seed;
	}
	//get info about x and y
	double X() const { return x; }
	double Y() const { return y; }
};

class LineSegment {
private:
	Point start, end;
public:
	LineSegment(const Point& p1, const Point& p2):start(p1),end(p2){}
	//a)
	//create hash for LineSegmenet
	friend std::size_t hash_value(const LineSegment& src) {
		std::size_t seed = 0;
		//get hash 
		boost::hash_combine<Point>(seed, src.start);
		boost::hash_combine<Point>(seed, src.end);
		return seed;
	}
};

#endif
