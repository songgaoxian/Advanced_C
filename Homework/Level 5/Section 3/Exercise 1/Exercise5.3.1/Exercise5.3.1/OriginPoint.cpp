//OriginPoint.cpp
//
//specify methods of OriginPoint
//written on 2016/6/29
#include"OriginPoint.hpp"
#include"Point.hpp"

OriginPoint::OriginPoint() :Singleton<Point>() {}

OriginPoint::OriginPoint(const OriginPoint& source) : Singleton<Point>(source) {}

OriginPoint& OriginPoint::operator=(const OriginPoint& source) {
	// Exit if same object
	if (this == &source) return *this;

	Singleton<Point>::operator = (source);

	return *this;
}

OriginPoint::~OriginPoint()
{ // Destructor
}