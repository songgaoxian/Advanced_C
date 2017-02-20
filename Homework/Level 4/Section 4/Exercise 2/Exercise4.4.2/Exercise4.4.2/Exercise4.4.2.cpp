//Exercise4.4.2
//
//apply hash on user-defined types and use user-defined hash
//written on 2016/6/20

#include"PointLine.h"
#include<list>
#include<sstream>

struct PointHash :std::unary_function<Point, std::size_t>
{
	std::size_t operator()(const Point& pt) const {
		/*std::size_t seed = 0;
		boost::hash_combine(seed, pt.X());
		boost::hash_combine(seed, pt.Y());*/
		//another possible implementation
		std::stringstream ss;
		//store parameters of pt as part of string
		ss << "(" << pt.X() << "," << pt.Y() << ")";
		//convert stringstream to string
		std::string s = ss.str();
		//get hashed value
		std::hash<std::string> hash;
		std::size_t seed = hash(s);
		return seed;
	}
};

int main() {
	//test a)
	std::cout << "a)\n";
	Point p(1.2, 2.3), p2(3.2, 3.3);
	std::cout<<"Hash value of p is "<< hash_value(p)<<'\n';
	LineSegment l(p, p2);
	std::cout<<"Hash value of l is "<< hash_value(l)<<'\n';

	//b)
	std::cout << "\nb)\n";
	//create a list of points
	std::list<Point> lstP{ Point(1,2),Point(3.3,2.3),Point(1.4,5.5) };
	//get hash
	std::size_t hash_lstp = boost::hash_range(lstP.begin(), lstP.end());
	std::cout << "Hashed value of lstP is " << hash_lstp << '\n';

	//c)
	std::cout << "\nc)\n";
	PointHash pth;
	//test function object
	std::cout << "Hash value of p is " << pth(p) << '\n';


	return 0;
}