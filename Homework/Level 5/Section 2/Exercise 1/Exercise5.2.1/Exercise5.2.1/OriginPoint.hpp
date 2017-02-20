//OriginPoint.h
//
//implement OriginPoint class
//written on 2016/6/29
#ifndef OriginPoint_H
#define OriginPoint_H

#include"Singleton.hpp"

class Point;
//a)create originpoint sub class
class OriginPoint :public Singleton<Point>
{
private:
	OriginPoint();//default constructor
	OriginPoint(const OriginPoint& source);//copy constructor
	OriginPoint& operator=(const OriginPoint& source);//assignment operator
public:
	virtual ~OriginPoint(); //destructor
};



#endif
