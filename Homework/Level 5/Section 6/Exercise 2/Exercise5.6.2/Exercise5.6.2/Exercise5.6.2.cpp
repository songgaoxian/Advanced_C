//Exercise5.6.2
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
	std::cout << "The exact distance btween p1 and p2=" << p1.Distance(p2,new ExactDistance) << '\n';
	//use approximate strategy
	std::cout << "The approximate distance btween p1 and p2=" << p1.Distance(p2,new ApproximateDistance) << '\n';
	return 0;
}