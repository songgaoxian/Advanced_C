#include"Function.h"
#include<iostream>

//c)find first value of 5
bool find5(int x) { return x == 5; }

//divide
bool Divide(int x, int y) { return x%y == 0; }

int main() {
	//test a)
	Vector v{ 1,2,4,5,4,1 };
	Vtuple result_a = count_f(v);
	//print result_a
	std::cout << "a)\n";
	for (auto it = result_a.begin(); it != result_a.end(); it++) {
		std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it) << ") ";
	}
	std::cout << '\n';
	
	//test b)
	std::vector<double> v1{ 1.4,3.6,5.2,1.8,9.9 };
	Tuple4 result_b = stat(v1);
	std::cout << "\nb)\n" << "min, max, sum and average are ";
	std::cout<< std::get<0>(result_b) << "," << std::get<1>(result_b) << ',' << std::get<2>(result_b) << ',' << std::get<3>(result_b);
	std::cout << '\n';

	//c)
	Vector vc{ 1,2,-3,4,5,5,5,6 };
	//find index of first occurrence of 5
	auto iterc = std::find(vc.begin(), vc.end(), 5);
	int index5=std::distance(vc.begin(),iterc);
	//find first index of even number with bind
	auto iterc1 = std::find_if(vc.begin(), vc.end(), std::bind(&Divide, std::placeholders::_1, 2));
	int indexEven1 = std::distance(vc.begin(),iterc1);
	//find first index of even number with bind2nd
	auto iterc2 = std::find_if(vc.begin(), vc.end(), std::bind2nd(std::ptr_fun(&Divide), 2));
	int indexEven2 = std::distance(vc.begin(),iterc2);
	//find first index of even number with lambda
	auto iterc3 = std::find_if(vc.begin(), vc.end(), [](int x) {return x % 2 == 0; });
	int indexEven3 = std::distance(vc.begin(),iterc3);
	std::cout << "\nc)\n5 occurs at index " << index5 << "\nthe indexes of first even number from three methods are " << indexEven1 << "," << indexEven2 << "," << indexEven3 << std::endl;
	
	//d)
	Vector vd{1,2,5,5,-3,4,5,5,5,6,3,4,5 };
	int nd = 3, vald = 5;
	//find index of first 3 consecutive 5 
	auto iterd1 = std::search_n(vd.begin(), vd.end(), nd, vald);
	int i3 = std::distance(vd.begin(),iterd1);
	Vector vdsub{ 3,4,5 };
	//find first match with {3,4,5}'s position
	auto iterd2 = std::find_first_of(vd.begin(), vd.end(), vdsub.begin(), vdsub.end());
	int i345fst = std::distance(vd.begin(),iterd2);
	//find last match with {3,4,5}'s position
	auto iterd3 = std::find_end(vd.begin(), vd.end(), vdsub.begin(), vdsub.end());
	int i345lst = std::distance(vd.begin(),iterd3);
	std::cout << "\nd)\nfirst 3 consecutive 5 occurs at " << i3 << "\nfirst match with {3,4,5} occurs at " << i345fst << "\nlast match occurs at " << i345lst << std::endl;

	//e)
	Vector ve{ 1,2,5,5,-3,4,5,5,5,6,3,4,5 };
	//find value of first consecutive 2 same elements
	int elemente = *std::adjacent_find(ve.begin(), ve.end());
	std::cout << "\ne)\n" << elemente << " is same as the following element\n";

	//f)
	Vector vf{ 1,2,5,5,-3,4,5,5,5,6,3,4,5 };
	Vector vfsub{ 1,2,5 };
	auto iterf = std::search(vf.begin(), vf.end(), vfsub.begin(), vfsub.end());
	if (iterf != vf.end()) {
		std::cout << "\nf)\n same elements are found earliest at "<<std::distance(vf.begin(),iterf)<<"\n";
	}
	else {
		std::cout << "\nf)\n no match is found\n";
	}


	return 0;

}