//DistanceStrategy.h
//
//create DistanceStrategy, ExactDistance and ApproximateDistance classes
//written on 2016/6/30

#ifndef DistanceStrategy_H
#define DistanceStrategy_H
class Point;
//a)create DistanceStrategy
class DistanceStrategy {
public:
	virtual double Distance(const Point& p1, const Point& p2) = 0;
};
//b)create ExactDistance
class ExactDistance :public DistanceStrategy
{
public:
	//implement Distance(), exact version
	virtual double Distance(const Point& p1, const Point& p2);
};
//c)create ApproximateDistance
class ApproximateDistance :public DistanceStrategy
{
public:
	//implement Distance(), approximate version
	virtual double Distance(const Point& p1, const Point& p2);
};
#include"Point.hpp"
#endif
