//Exercise4.10.5
//
//unified vector interface using Template Template parameters
//written on 2016/6/25
#include<boost\numeric\ublas\vector.hpp>
#include<vector>
#include<list>
#include<iostream>
#include<algorithm>
#include<tuple>
#include<string>
#include<complex>

//first parameter stores the index where match is found
using Result = std::tuple<std::size_t, bool>;//false: no match; true: match found

//create search generic function
template<typename T, typename Alloc1, typename Alloc2,
	template<typename S1,typename TAlloc1>
    class Container1,
	template<typename S2,typename TAlloc2>
	class Container2
>
Result search(std::string str, const Container1<T, Alloc1>& container1, const Container2<T, Alloc2>& container2)
{
		std::cout << str << '\n';
		//predicate
		auto equal = [](T t1, T t2) {return t1 == t2; };
		//apply std::search
		auto it=std::search(container1.begin(), container1.end(), container2.begin(), container2.end(), equal);
		//check if exist match
		if (it != container1.end()) {
			std::size_t index = std::distance(container1.begin(), it);
			return std::make_tuple(index, true);
		}
		else {
			return std::make_tuple(-1, false);//no match
		}
}

	
	
int main() {
	//test case 1
	//initialize vector to be searched
	std::vector<double> vd{2,3,1, 1,2,3,4,5,6 };
	//initialise vector representing match
	boost::numeric::ublas::vector<double> uvd(3);
	uvd[0] = 1; uvd[1] = 2; uvd[2] = 3;
	//conduct search
	Result r = search("std vector and boost vector:", vd, uvd);
	//print out
	std::boolalpha(std::cout);
	std::cout << "Is there a match in vd for uvd sequence? " << std::get<1>(r) << '\n';
	std::cout <<"The match starts in index "<<std::get<0>(r) << '\n';

	//test case 2
	using c_double = std::complex<double>;
	boost::numeric::ublas::vector<c_double> uvc(5);
	uvc[0] = 0.1; uvc[1] = 0.5; uvc[2] = 1.8; uvc[3] = 0.9, uvc[4] = 1.1;
	std::list<c_double> lst;
	lst.push_back(0.5); lst.push_back(1.8); lst.push_back(0.9);
	//search
	r = search("\nboost vector and std list with complex numbers:", uvc, lst);
	//print out
	std::cout << "Is there a match in uvc for lst sequence? " << std::get <1>(r) << '\n';
	std::cout << "The match starts in index " << std::get<0>(r) << '\n';

	return 0;
}
