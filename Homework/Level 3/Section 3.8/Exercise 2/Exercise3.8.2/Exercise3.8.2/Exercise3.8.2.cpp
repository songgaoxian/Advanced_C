#include<random>
#include<map>
#include<iostream>
#include<string>

std::map<long long, int> counter;

template<typename Dist, typename Eng>
void GenerateRandomNumbers(Dist d, Eng eng, int NTrials, const std::string& s) {
	std::cout << s << std::endl;
	//clear contents of counter
	counter.clear();
	for (int i = 0; i < NTrials; ++i) {
		//generate random variate
		long long temp = d(eng);
		//check if counter already has the value
		if (counter.count(temp) > 0)
			counter[temp] += 1;
		else
			counter[temp] = 1;
	}
	//print the histogram
	for (auto it = counter.begin(); it != counter.end(); ++it) {
		std::cout << it->first << ":"<<(double)it->second/(double)NTrials;
		std::cout << '\n';
	}
		
}


int main() {
	using Geo = std::geometric_distribution<long long>;
	using Uni = std::uniform_int_distribution<long long>;
	using Poi = std::poisson_distribution<long long>;
	//give instances of Geo, Uni and Poi
	Geo gdist(0.4);
	Uni udist(1, 7);
	Poi pdist(5.1);
	using Deng = std::default_random_engine;
	Deng eng;
	int N = 800;
	//get frequency/N: similar to real probability
	GenerateRandomNumbers<Geo, Deng>(gdist, eng, N, "Geometric Distribution");
	GenerateRandomNumbers<Uni, Deng>(udist, eng, N, "Uniform Distribution");
	GenerateRandomNumbers<Poi, Deng>(pdist, eng, N, "Poisson Distribution");
	
	return 0;
}