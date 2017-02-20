#include<random>
#include<iostream>
#include<map>
#include<algorithm>
//a)
//N: total number of observations, n: number of cells in the table
//get Chi-squared statistic
template<typename value_type, std::size_t N, std::size_t n>
double ChiStatic(std::map<value_type, int>& O, std::map<value_type, double>& p) {
	//the size of O and p equal to n
	double A2 = 0.0;
	for (auto it = O.begin(); it != O.end(); it++) {
		//get simulated frequency
		double frequency = (double)it->second / (double)N;
		//get theoretical probability
		double pi = p[it->first];
		A2 += (frequency - pi)*(frequency - pi) / pi;
	}
	A2 *= (double)N;
	return A2;
}

//print out histogram
void histogram(std::vector<double>& v) {
	//get boundary of v
	auto bounds = std::minmax_element(v.begin(), v.end());
	double min = *bounds.first;
	double max = *bounds.second;
	//get interval of histogram
	double difference = (max - min) / 50.0;
	//get start value
	double start = min + difference;
	while (start <= max) {
		auto compare = [=](double x) {return (x >= start - difference) && (x < start); };
		int count = std::count_if(v.begin(), v.end(), compare);
		//print out histogram
		for (int i = 0; i < count; ++i)
			std::cout << '*';
		std::cout << '\n';
		start += difference;
	}
}


int main() {
	//b)
	std::random_device rd;
	std::mt19937_64 g1(rd());
	const int n = 5;
	const int N = 669;
	//binomial distribution
	std::binomial_distribution<int> binon(n,0.5);
	//use O record occurrencies of 0 to 5
	std::map<int, int> O;
	//record real probability
	std::map<int, double> p;
	p[0] = 0.03125;
	p[1] = 0.15625;
	p[2] = 0.3125;
	p[3] = 0.3125;
	p[4] = 0.15625;
	p[5] = 0.03125;
	//store chi-squared statistic
	std::vector<double> Chi;
	int NTrials = 500;
	for (int i = 0; i < NTrials; ++i) {
		//set initial status
		for (int m = 0; m <= n; ++m) {
			O[m] = 0;
		}
		for (int j = 0; j < N; ++j) {
			O[binon(g1)]++;
		}
		Chi.push_back(ChiStatic<int, N, n>(O, p));
	}
	//print out histogram
	std::cout << "print out Chi histogram using binonmial distribution to check:\n";
	histogram(Chi);

	//c)
	O.clear();
	p.clear();
	Chi.clear();
	const int k = 20;
	std::uniform_int_distribution<int> uintD(0, k);
	//set probability
	for (int i = 0; i <= k; ++i) {
		p[i] = 1.0 / ((double)k + 1.0);
	}
	const int NDraw = 400;
	for (int i = 0; i < NTrials; ++i) {
		//initialise O
		for (int m = 0; m <= k; ++m) {
			O[m] = 0;
		}
		//generate observations
		for (int j = 0; j < NDraw; ++j) {
			O[uintD(g1)]++;
		}
		//compute Chi statistic
		double chiStat = ChiStatic<int, NDraw, k>(O, p);
		Chi.push_back(chiStat);
	}
	//print out histogram
	std::cout << "\nprint histogram of Chi-squared by using uniform distribution\n";
	histogram(Chi);


	return 0;
}