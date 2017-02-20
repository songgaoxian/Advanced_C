#ifndef Shape_H
#define Shape_H
#include "ClassDeclaration.h"
#include "IODevice.h"
#include<iostream>
#include<string>
class Shape {
public:
	virtual void display(IODevice& ioDevice) const = 0;
};

class Circle :public Shape {
private:
	double coordinateX;
	double coordinateY;
	double radius;
public:
	Circle():coordinateX(0),coordinateY(0),radius(0){}
	Circle(double x, double y, double r);
	virtual void display(IODevice& circleIO) const;
	std::string Circleinfo() const;
};

class Line :public Shape {
private:
	double xStartPoint;
	double yStartPoint;
	double xEndPoint;
	double yEndPoint;
public:
	Line():xStartPoint(0),yStartPoint(0),xEndPoint(0),yEndPoint(0){}
	Line(double x1, double y1, double x2, double y2);
	virtual void display(IODevice& lineIO) const;
	std::string Lineinfo() const;
};
#endif