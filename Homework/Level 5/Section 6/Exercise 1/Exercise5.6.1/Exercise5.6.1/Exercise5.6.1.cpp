//Exercise5.6.1
//
//calculate distance btw points using different strategies
//written on 2016/6/30

#include"Point.hpp"
#include"DistanceStrategy.hpp"
//f)
int main() {
	//create two points
	Point p1(3.0, 4.0);
	Point p2(0, 0);
	//use exact strategy
	Point::SetStrategy(new ExactDistance);
	std::cout << "The exact distance btween p1 and p2=" << p1.Distance(p2) << '\n';
	//use approximate strategy
	Point::SetStrategy(new ApproximateDistance);
	std::cout << "The approximate distance btween p1 and p2=" << p1.Distance(p2) << '\n';
	return 0;
}