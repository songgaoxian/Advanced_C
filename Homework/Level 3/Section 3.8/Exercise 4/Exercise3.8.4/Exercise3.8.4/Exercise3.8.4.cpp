#include<random>
#include<iostream>

int main() {
	//a)create random engine and set its seed
	std::random_device rd;
	std::default_random_engine rEng;
	rEng.seed(rd());
	//b)two instances of std::uniform_real_distribution
	std::uniform_real_distribution<double> ud1(0.0, 1.0);
	std::uniform_real_distribution<double> ud2(0.0, 1.0);
	//c)
	//initialise the counter
	long long counter = 0;
	long long Ntrials = 2000000000;
	for (long long i = 0; i < Ntrials; ++i) {
		if (i % 10000000 == 0) std::cout << "* ";
		double x = ud1(rEng);
		double y = ud2(rEng);
		//if pythagorean distance to origin greater than 1, increment counter
		if (x*x + y*y > 1.0)
			counter++;
	}
	//d)compute pi 
	long double pi = (long double)(Ntrials - counter) / (long double)Ntrials*4.0;
	std::cout << "Ntrials " << Ntrials << ": " << pi << '\n';
	//it takes around 2000000000 to get pi near 3.14159
	return 0;

}