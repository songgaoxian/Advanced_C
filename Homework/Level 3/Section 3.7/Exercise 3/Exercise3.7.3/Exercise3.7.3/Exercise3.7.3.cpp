#include<vector>
#include<algorithm>
#include<numeric>
#include<iostream>
#include<string>
#include<set>
#include<random>

using Vector = std::vector<double>;

int main() {
	Vector v{ 1,2,3,4 };
	//a)scale all values by a given factor
	std::cout << "a)\n";
	double factor = 2;
	//modifying algorithm (C2)
	std::transform(v.begin(), v.end(), v.begin(), [=](double x) {return x*factor; });
	std::cout << "after scalar multiply:\n";
	//print out 2 4 6 8
	std::for_each(v.begin(), v.end(), [](double x) {std::cout << x << " "; });
	
	//b)count number of elements whose values are in a given range
	std::cout << "\nb)\n";
	double low = 2.5, up = 6.3;//captured variables
	//Nonmodifying (C1)
	std::cout<<"b: number of elements within range="<<std::count_if(v.begin(), v.end(), [=](double x) {return (x > low) && (x < up); })<<std::endl;

	//c)Find average
	double ini = 0;
	//C7: Numeric
	double average = std::accumulate(v.begin(), v.end(), ini) / v.size();
	//Find minmax value in  a container
	//C1:Nonmodify
	auto minmax = std::minmax_element(v.begin(), v.end());
	std::cout << "\nc)\n";
	std::cout << "v's average=" << average << "; v's min and max are " << *minmax.first << " and " << *minmax.second << std::endl;
	
	//d)Find first element not in a range=(low,up)
	//C1: Nonmodify
	std::cout << "\nd)\n";
	double element = *std::find_if_not(v.begin(), v.end(), [=](double x) {return (x > low) && (x < up); });
	std::cout << "first element not in (low, up) is " << element << std::endl;

	//e)Search for all occurrences of '3456' in the container
	//C1: Nonmodify
	Vector v2{ 3,4,5,6,1,2,3,3,4,5,6,7,1,3,4,5,6 };
	Vector vsub{ 3,4,5,6 };
	//search for 3456
	auto pos = std::search(v2.begin(), v2.end(), vsub.begin(), vsub.end());
	std::cout << "\ne)\n";
	std::cout << "3456 occurs at the following indexes:\n";
	while (pos != v2.end()) {
		std::cout << std::distance(v2.begin(), pos) << " ";
		pos = std::search(++pos, v2.end(), vsub.begin(), vsub.end());
	}
	std::cout << std::endl;

	//f)Determine if elements in two ranges are equal
	Vector v3(v2);
	v3[2] = 30;
	//C1 Nonmodify
	std::cout << "\nf)\n";
	std::cout << "Is v3 equal to v2 for first 3 elements ? " << std::boolalpha << std::equal(v2.begin(), v2.begin()+3, v3.begin())<<std::endl;

	//g)Determine if a set is some permutation of '12345'
	int arr[] = { 1,2,3,4,5 };
	std::set<int> s(arr, arr + 5);
	int arr2[] = { 2,1,5,4,3 };
	std::set<int> s2(arr2, arr2 + 5);
	//C1 Nonmodify
	std::cout << "\ng)\n";
	std::cout << "Is s2 some permutation of 12345? " << std::boolalpha << std::is_permutation(s2.begin(), s2.end(), s.begin())<<std::endl;

	//h)Is a container sorted?
	//C1 Nonmodify
	std::cout << "\nh)\n";
	std::cout << "Is v2 sorted? " << std::boolalpha << std::is_sorted(v2.begin(), v2.end()) << std::endl;

	//i)copy a container into another container
	//C2 Modify
	Vector vt{ 2,2,2,2 };
	std::copy(v.begin(), v.end(), vt.begin());
	std::cout << "\ni)\n";
	std::for_each(vt.begin(), vt.end(), [](double x) {std::cout << x << " "; });
	std::cout << std::endl;

	//j)move last 10 elements to front
	Vector vj{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	//C4 Mutating
	std::rotate(vj.begin(), vj.end() - 10, vj.end());
	std::cout << "\nj)\n";
	std::for_each(vj.begin(), vj.end(), [](double x) {std::cout << x << " "; });
	std::cout << std::endl;

	//k)swap two ranges at given position
	Vector vk1{ 1,3,45,77 };
	Vector vk2{ 6,2,43,99 };
	//C2 Modify
	std::swap_ranges(vk1.begin(), vk1.begin() + 3, vk2.begin() + 1);
	std::cout << "\nk)\n";
	std::for_each(vk1.begin(), vk1.end(), [](double x) {std::cout << x << " "; });
	std::cout << std::endl;
	std::for_each(vk2.begin(), vk2.end(), [](double x) {std::cout << x << " "; });
	std::cout << std::endl;

	//l)generate values in a container based on some formula
	//C2 Modify
	std::vector<int> vl(10);
	std::generate(vl.begin(), vl.end(), []() {return std::rand()%150; });
	std::cout << "\nl)\n";
	std::for_each(vl.begin(), vl.end(), [](int x) {std::cout << x << " "; });
	std::cout << std::endl;

	//m)replace all uneven numbers by zero
	//C2 Modify
	std::replace_if(vl.begin(), vl.end(), [](int x) {return x % 2 == 1; }, 0);
	std::cout << "\nm)\n";
	std::for_each(vl.begin(), vl.end(), [](int x) {std::cout << x << " "; });
	std::cout << std::endl;

	//n)remove all elements whose value is less than 100
	//C3 Remove
	auto itend=std::remove_if(vl.begin(), vl.end(), [](int i) {return i < 100; });
	std::cout << "\nn)\n";
	std::for_each(vl.begin(), itend, [](int x) {std::cout << x << " "; });
	std::cout << std::endl;

	//o)Shuffle a container
	//C4 Mutate
	std::vector<int> vo{ 2,3,4,5,6 };
	unsigned g = 300;
	std::shuffle(vo.begin(), vo.end(), std::default_random_engine(g));
	std::cout << "\no)\n";
	std::for_each(vo.begin(), vo.end(), [](int x) {std::cout << x << " "; });
	std::cout << std::endl;

	//p)one-sided divided differences of values in a container
	//C7 Numeric
	std::adjacent_difference(vo.begin(), vo.end(), vo.begin());
	std::cout << "\np)\n";
	std::for_each(vo.begin(), vo.end(), [](int x) {std::cout << x << " "; });
	std::cout << std::endl;


	return 0;
}