//Line.hpp
//
//declare Line class
//written on 2016/7/14

#ifndef Line_HPP
#define Line_HPP

#include"Shape.hpp"
#include"Point.hpp"

class Line :public Shape
{
private:
	Point start_pt, end_pt;
public:
	//default constructor
	Line();
	//constructor with points
	Line(const Point& pt1s, const Point& pt2s);
	//copy constructor
	Line(const Line& line);
	//assignment operator
	Line& operator=(const Line& line);
	//getter of start point
	Point p1() const;
	//getter of end point
	Point p2() const;
	//setter of start point
	void p1(const Point& ps);
	//setter of end point
	void p2(const Point& ps);

	friend std::ostream& operator<<(std::ostream& os, const Line& line);
	//de)calculate length of the line
	double Length() const;
};



#endif

