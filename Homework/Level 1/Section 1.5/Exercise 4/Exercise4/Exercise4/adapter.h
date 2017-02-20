#ifndef Adapter_H
#define Adapter_H
#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>
#include<tuple>
#include<cmath>

template<typename T>
struct AdaptorIndex {
private:
	std::vector<T> vc;
public:
	AdaptorIndex(const AdaptorIndex&& src) {
		vc = std::move(src.vc);
	}
	AdaptorIndex() {
		vc.push_back(0);
	}
	AdaptorIndex(std::vector<T>&& src){
		vc = std::move(src);
	}
	~AdaptorIndex() {}
	std::size_t operator()(T x) {
		std::sort(vc.begin(), vc.end(), [](T first, T second) {return (first < second); });
		std::vector<T>::iterator it = std::find_if(vc.begin(), vc.end(), [=](T ele) {return (x < ele); });
		it--;
		return std::distance(vc.begin(), it);
	}
};
template<typename T>
struct AdapterErr {
private:
	std::vector<T> v1;
	std::vector<T> v2;
public:
	AdapterErr() {
		v1.push_back(0);
		v2.push_back(0);
	}
	AdapterErr(const AdapterErr&& adpe) {
		v1 = std::move(adpe.v1);
		v2 = std::move(adpe.v2);
	}
	AdapterErr(std::vector<T>&& src1, std::vector<T>&& src2) {
		v1 = std::move(src1);
		v2 = std::move(src2);
	}
	~AdapterErr() {}
	std::tuple<std::size_t, T, std::size_t, T> operator()(int start, int end) const {
		std::vector<T> absErr, relativeErr;
		T err;
		for (unsigned int i = 0; i < v1.size();i++) {
			err= std::abs(v1[i] - v2[i]);
			absErr.push_back(err);
			err=err/ std::abs(v1[i]);
			relativeErr.push_back(err);
		}
		std::vector<T>::iterator sit = absErr.begin() + start;
		std::vector<T>::iterator eit = absErr.begin() + end;
		auto absIt = std::max_element(sit, eit);
		sit = relativeErr.begin() + start;
		eit = relativeErr.begin() + end;
		auto relativeIt = std::max_element(sit, eit);
		T maxAbs = *absIt;
		T maxRelative = *relativeIt;
		std::size_t maxAbsIndex = std::distance(absErr.begin(), absIt);
		std::size_t maxRelativeIndex = std::distance(relativeErr.begin(), relativeIt);
		std::tuple<std::size_t, T, std::size_t, T> result = std::make_tuple(maxAbsIndex, maxAbs, maxRelativeIndex, maxRelative);
		
		
		return result;
	}
};

#endif