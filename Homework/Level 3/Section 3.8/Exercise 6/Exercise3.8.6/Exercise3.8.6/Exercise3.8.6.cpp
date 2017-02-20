#include<boost/random/lagged_fibonacci.hpp>
#include<boost/random/triangle_distribution.hpp>
#include<boost/random/generate_canonical.hpp>
#include<boost/random/mersenne_twister.hpp>
#include<vector>

//print out to check uniformity of generate_canonical
void print(std::vector<double>& sv,double val) {
	int counter = 0;
	for (auto it = sv.begin(); it != sv.end(); ++it) {
		if (*it < val)
			counter++;
	}
	std::cout << "less than " << val << ": " << (double)counter / (double)sv.size() << '\n';
}

int main() {
	//a)
	//create lagged_fibonacci engine
	boost::lagged_fibonacci607 leng;
	//create triangle distribution
	boost::triangle_distribution<double> tdist(0.0, 0.5, 1.0);
	//generate variate of triangle distribution
	auto variate = tdist(leng);
	std::cout << variate << '\n';
	//b)
	//experiment with 8
	std::vector<double> vc;
	boost::mt19937 mEng;
	int N = 9000;
	for (int i = 0; i < N; ++i) {
		double result = boost::random::generate_canonical<double, 8, boost::mt19937>(mEng);
		vc.push_back(result);
	}
	std::cout << "\ntest with bits of 8:\n";
	print(vc, 0.2);
	print(vc, 0.4);
	print(vc, 0.6);

	//experiment with 16
	vc.clear();
	//assign a different seed
	mEng.seed(1234);
	for (int i = 0; i < N; ++i) {
		double result = boost::random::generate_canonical<double, 16, boost::mt19937>(mEng);
		vc.push_back(result);
	}
	std::cout << "\ntest with bits of 16:\n";
	print(vc, 0.2);
	print(vc, 0.4);
	print(vc, 0.6);

	//experiment with 32
	vc.clear();
	for (int i = 0; i < N; ++i) {
		double result = boost::random::generate_canonical<double, 16, boost::mt19937>(mEng);
		vc.push_back(result);
	}
	std::cout << "\ntest with bits of 32:\n";
	print(vc, 0.2);
	print(vc, 0.4);
	print(vc, 0.6);

	return 0;

}