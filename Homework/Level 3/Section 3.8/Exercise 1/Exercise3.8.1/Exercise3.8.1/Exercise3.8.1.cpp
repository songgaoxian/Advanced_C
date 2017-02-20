#include<random>
#include<iostream>
#include<list>

template<typename Engine, typename Distribution, typename value_type>
std::list<value_type> generate(Engine& eng, Distribution& dist) {
	std::list<value_type> result;
	//push random variates to list
	for (int i = 0; i < 10; ++i) {
		result.push_back(dist(eng));
	}
	return result;
}
//print out contents of a list
template<typename T>
void print(std::list<T>& lst) {
	//print out content of lst
	for (auto it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

int main() {
	//a)
	//copied
	std::default_random_engine eng;
	//generate uniform variates
	double A = 0.0;
	double B = 1.0;
	//std::uniform_real_distribution<double> dist(A, B);
	//b)
	//normal
	//std::normal_distribution<double> dist(A, B);
	//chi-squared
	//int freedom = 3;
	//std::chi_squared_distribution<double> dist(freedom);
	//bernouli
	//double p = 0.2;
	//std::bernoulli_distribution dist(p);
	//cauchy
	std::cauchy_distribution<double> dist(A, B);
	int nTrials = 30;
	for (int i = 1; i <= nTrials; ++i)
		std::cout << dist(eng) << ", ";
	std::cout << '\n';

	//adapted by using linear_congruential_engine
	//minstd_rand0
	std::linear_congruential_engine<std::uint_fast32_t,16807,0,2147483647> eng2;
	//std::uniform_real_distribution<double> dist2(A, B);
	//b)
	//normal
	//std::normal_distribution<double> dist2(A, B);
	//chi-squared
	//int free2 = 3;
	//std::chi_squared_distribution<double> dist2(free2);
	//bernoulli
	//std::bernoulli_distribution dist2(0.3);
	//cauchy
	std::cauchy_distribution<double> dist2(A, B);
	//display uniform distributed variates
	for (int i = 1; i <= nTrials; ++i)
		std::cout << dist2(eng2) << ", ";
	std::cout << '\n';

	//using mt19937
	std::mt19937 eng3;
	//std::uniform_real_distribution<double> dist3(A, B);
	//b)
	//normal
	//std::normal_distribution<double> dist3(A, B);
	//chi-squared
	//std::chi_squared_distribution<double> dist3(4);
	//bernoulli
	//std::bernoulli_distribution dist3(0.4);
	//cauchy
	std::cauchy_distribution<double> dist3(A, B);
	//display uniform distributed variates
	for (int i = 1; i <= nTrials; ++i)
		std::cout << dist3(eng3) << ", ";
	std::cout << '\n';

	//using mt19937_64
	std::mt19937_64 eng4;
	//std::uniform_real_distribution<double> dist4(A, B);
	//b)
	//normal
	//std::normal_distribution<double> dist4(A, B);
	//chi-square
	//std::chi_squared_distribution<double> dist4(7);
	//bernoulli
	//std::bernoulli_distribution dist4(0.5);
	//cauchy
	std::cauchy_distribution<double> dist4(A, B);
	//display uniform distributed variates
	for (int i = 1; i <= nTrials; ++i)
		std::cout << dist4(eng4) << ", ";
	std::cout << '\n';

	//c)
	using Dlist = std::list<double>;
	//specify distribution types
	using Normal = std::normal_distribution<double>;
	using Uniform = std::uniform_real_distribution<double>;
	using Chi = std::chi_squared_distribution<double>;
	using Bern = std::bernoulli_distribution;
	using Cauchy = std::cauchy_distribution<double>;
	//specify engines
	using DefaultE = std::default_random_engine;
	using LinearE = std::linear_congruential_engine<std::uint_fast32_t, 16807, 0, 2147483647>;
	using mt19937 = std::mt19937;
	using mt1993764 = std::mt19937_64;

	Dlist result;
	std::list<int> result2;
	//give distribution instances
	Uniform db1(A, B);
	Normal db2(A, B);
	Chi db3(3);
	Bern db4(0.5);
	Cauchy db5(A, B);
	//give engine instances
	DefaultE e1;
	LinearE e2;
	mt19937 e3;
	mt1993764 e4;

	std::cout << '\n';
	//test some cases
	result = generate<DefaultE, Uniform, double>(e1, db1);
	print<double>(result);
	//test LinearE and Normal
	result = generate<LinearE, Normal, double>(e2, db2);
	print<double>(result);
	//test mt19937 and Bern
	result2 = generate<mt19937, Bern, int>(e3, db4);
	print<int>(result2);
	//test mt1993764 and cauchy
	result = generate<mt1993764, Cauchy, double>(e4, db5);
	print<double>(result);
	//test LinearE and Chi-square
	result = generate<LinearE, Chi, double>(e2, db3);
	print<double>(result);
	
	return 0;

}