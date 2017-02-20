//Exercise4.4.4
//
//apply variadic hash
//written on 2016/6/20

#include"Shape.h"
//a)//create hash function using a seed
template<typename T>
void hash_value(std::size_t& seed, const T& val) {
	//the final step
	boost::hash_combine(seed, val);
}
template<typename T, typename...Types>
void hash_value(std::size_t& seed, const T& val, const Types... args) {
	boost::hash_combine(seed, val);
	//call hash_value recursively
	hash_value(seed, args...);
}
//b)
template<typename... Types>
std::size_t hash_value(const Types&... args) {
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}

int main() {
	//a)create variables for test
	std::string s1("hello");
	std::string s2("let's be friends");
	int num = 99;
	double dnum = 44.5;
	double * dptr = &dnum;
	std::complex<double> cplex(1.2, 3.3);
	std::vector<double> vd{ 1.2,3.3,8.8,9.9,7.6 };
	std::size_t seed = 0;
	hash_value(seed, s1, s2, num, dnum, dptr,cplex,vd);
	std::cout << "after all, seed=" << seed << '\n';

	//b)
	//same test case as in a)
	std::size_t bseed = hash_value(s1, s2, num, dnum, dptr, cplex, vd);
	std::cout << "For same args, seed=" << bseed << '\n';
	//compositions
	std::complex<double> cplex2(1.7, 3.4);
	std::complex<double> cplex3(7.7, 3.5);
	using cDouble = std::complex<double>;
	std::vector<cDouble> vcd{ cplex,cplex2,cplex3 };
	std::vector<cDouble> vcd2{ cplex,cplex2 };
    //get seeds for different compositions
	std::size_t seed1 = hash_value(cplex, cplex2, cplex3);
	std::size_t seed2 = hash_value(vcd);
	std::size_t seed3 = hash_value(vcd2, cplex3);
	//print out these seeds
	std::cout << "For args composed of cDoubles, seed=" << seed1 << '\n';
	std::cout << "For args composed of vector of 3 cDoubles, seed=" << seed2 << '\n';
	std::cout << "For args composed of one vector of 2 cDoubles and one cDouble,seed=" << seed3 << '\n';

	Point pt1(1.1, 0.9), pt2(2.3, 4.5), pt3(5.5, 3.9);
	Triangle triang(pt1, pt2, pt3);
	seed1 = hash_value(triang);
	seed2 = hash_value(pt1, pt2, pt3);
	std::vector<Point> vp{ pt1,pt2,pt3 };
	seed3 = hash_value(vp);
	//print out these seeds
	std::cout << "For triangle: seed=" << seed1 << '\n';
	std::cout << "For three points: seed=" << seed2 << '\n';
	std::cout << "For vector of three points: seed=" << seed3 << '\n';

	return 0;
}