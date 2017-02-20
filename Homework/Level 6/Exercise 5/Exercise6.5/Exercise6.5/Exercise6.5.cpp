//Exercise6.5
//
//test strategy pattern codes implemented with dist_algo

#include"Point.hpp"
#include"Point2.hpp"
#include<future>
//phytagoras algorithm
dist_algo exactDist = [](double x1, double y1, double x2, double y2,int& count)->double {
	count++;
	double diff_x = x2 - x1;
	diff_x *= diff_x;
	double diff_y = y2 - y1;
	diff_y *= diff_y;
	return std::sqrt(diff_x + diff_y);
};
//taximan algorithm
dist_algo approximateDist = [](double x1, double y1, double x2, double y2,int& count)->double {
	count++;
	return std::abs(x1 - x2) + std::abs(y1 - y2);
};


int main() {
	//test stateless version
	Point pt1(1, 2);
	Point pt2(2, 3);
	//compute distances
	std::future<double> pt1_exact = std::async(&Point::Distance, &pt1, pt2, exactDist);
	std::future<double> pt1_approx = std::async(&Point::Distance, &pt1, pt2, approximateDist);
	
	//test statebased version
	Point2 pt3(1, 2, exactDist);
	Point2 pt4(2, 3, approximateDist);
	//compute distances
	std::future<double> pt3_exact = std::async(&Point2::Distance, &pt3, pt4);
	std::future<double> pt4_approx = std::async(&Point2::Distance, &pt4, pt3);

	//print distances
	std::cout << "exact distance between pt1 and pt2: " << pt1_exact.get() << '\n';
	std::cout << "approximate distance between pt1 and pt2: " << pt1_approx.get() << '\n';
	std::cout << "exact distance between pt3 and pt4: " << pt3_exact.get() << '\n';
	std::cout << "approximate distance between pt3 and pt4: " << pt4_approx.get() << '\n';
	
	//print out the static counters
	std::cout << "Point's static counter=" << Point::Getcounter() << '\n';
	std::cout << "Point2's static counter=" << Point2::Getcounter() << '\n';

	return 0;
}
