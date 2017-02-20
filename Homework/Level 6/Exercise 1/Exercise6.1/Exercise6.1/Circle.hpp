//Circle.hpp
//
//declare class Circle
//written on 2016/7/14

#ifndef Circle_HPP
#define Circle_HPP

#include"Shape.hpp"
#include"Point.hpp"

class Circle :public Shape
{
private:
	Point m_centre;
	double m_r;
public:
	//default constructor
	Circle();
	//constructor with point and radius
	Circle(const Point& c, double r);
	//copy constructor
	Circle(const Circle& c);
	//assignment operator
	Circle& operator=(const Circle& c);
	//getter of centre
	Point CenterPoint() const;
	//getter of radius
	double Radius() const;
	//setter of centre
	void CenterPoint(Point centre);
	//setter of radius
	void Radius(double radius);

	friend std::ostream& operator<<(std::ostream& os, const Circle& c);
};

#endif
