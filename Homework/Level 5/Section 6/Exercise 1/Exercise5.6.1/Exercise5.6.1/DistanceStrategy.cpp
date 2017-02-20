//DistanceStrategy.cpp
//
//implement DistanceStrategy and derived classes
//written on 2016/6/30
#include"DistanceStrategy.hpp"
#include"Point.hpp"

double ExactDistance::Distance(const Point& p1, const Point& p2) {
	double diff_x = p1.X() - p2.X();
	double diff_y = p1.Y() - p2.Y();
	diff_x *= diff_x;
	diff_y *= diff_y;
	return sqrt(diff_x + diff_y);
}

double ApproximateDistance::Distance(const Point& p1, const Point& p2) {
	double diff_x = p1.X() - p2.X();
	double diff_y = p1.Y() - p2.Y();
	return abs(diff_x) + abs(diff_y);
}