#include"OriginPoint.hpp"
#include"Point.hpp"
#include"Singleton.hpp"
#include<iostream>

int main() {
	//d)test program
	Point p(3, 4);
	double dist = p.Distance();
	std::cout << "distance between " << p << " and " << *OriginPoint::instance() << " is " << dist << '\n';
	//change origin point
	OriginPoint::instance()->X(3);
	OriginPoint::instance()->Y(4);
	//calculate distance again
	dist = p.Distance();
	std::cout << "distance between " << p << " and " << *OriginPoint::instance() << " is " << dist << '\n';

	return 0;

}