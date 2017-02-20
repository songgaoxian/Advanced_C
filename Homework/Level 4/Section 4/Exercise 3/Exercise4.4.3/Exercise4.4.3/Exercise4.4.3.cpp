//Exercise4.4.3
//
//use unordered collections for different types
//written on 2016/6/20

#include<string>
#include<bitset>
#include<unordered_set>
#include<functional>
#include<iostream>
#include<chrono>
#include<set>
#include"Point.h"

//a)user-defined hash for class Point based on std::hash
struct hash_std :std::unary_function<Point, std::size_t> {
	std::size_t operator()(const Point& p) const {
		//create a hash for string
		std::hash<std::string> sHash;
		//return hash 
		return sHash(p.Point_s());
	}
};

//b)self-defined hash function
struct myHash:std::unary_function<Point,std::size_t>
{
	std::size_t operator()(const Point& p) const {
		int x = int(12.0*p.X());
		int y = int(19.0*p.Y());
		std::size_t key = std::abs(x + y);
		//create bitset
		std::bitset<24> bs(key*key);
		std::size_t factor = 1;
		//extract the middle 10 digits to be the hash value
		std::size_t hash = 0;
		for (std::size_t i = 6; i < 16; ++i) {
			hash += factor*bs[i];
			factor *= 2;
		}
		return hash;
	}
};


int main() {
	//a)create an unordered multiset of Point
	std::unordered_multiset<Point, hash_std> ptmset;
	int N = 8000;
	double xval;
	double yval;
	//create start and end to record starting and ending time points
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	//record starting time
	start = std::chrono::system_clock::now();
	//add many points to multiset
	for (int i = 0; i < N / 2; ++i) {
		int temp = rand() % 800;
		xval = temp / 13.0;
		temp = rand() % 800;
		yval = temp / 13.0;
		ptmset.insert(Point(xval, yval));
		temp = rand() % 800;
		xval = temp / 13.0;
		temp = rand() % 800;
		yval = temp / 13.0;
		ptmset.emplace(Point(xval, yval));
	}
	//record end time
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "a)\nIt takes " << duration.count() << " seconds to insert and emplace.\n";
	
	//erase elements
	//record start time
	start = std::chrono::system_clock::now();
	for (int i = 0; i < N / 2; ++i) {
		ptmset.erase(ptmset.begin());
	}
	//clear elements
	ptmset.clear();
	//record ending time
	end = std::chrono::system_clock::now();
	//get duration
	duration = end - start;
	std::cout << "It takes " << duration.count() << " seconds to erase and clear elements\n";

	//b)use self-created hash function object myHash
	std::unordered_multiset<Point, myHash> ptmset2;
	//record starting time
	start = std::chrono::system_clock::now();
	//add many points to multiset
	for (int i = 0; i < N / 2; ++i) {
		int temp = rand() % 800;
		xval = temp / 13.0;
		temp = rand() % 800;
		yval = temp / 13.0;
		ptmset2.insert(Point(xval, yval));
		temp = rand() % 800;
		xval = temp / 13.0;
		temp = rand() % 800;
		yval = temp / 13.0;
		ptmset2.emplace(Point(xval, yval));
	}
	end = std::chrono::system_clock::now();
	duration = end - start;
	std::cout << "\nb)\nIt takes " << duration.count() << " seconds to insert and emplace.\n";
	
	//erase elements
	start = std::chrono::system_clock::now();
	for (int i = 0; i < N / 2; ++i) {
		ptmset2.erase(ptmset2.begin());
	}
	//clear elements
	ptmset2.clear();
	//record ending time
	end = std::chrono::system_clock::now();
	//get duration
	duration = end - start;
	std::cout << "It takes " << duration.count() << " seconds to erase and clear\n";

	//c)
	std::multiset<Point> mset;
	//record starting time
	start = std::chrono::system_clock::now();
	//add many points to multiset
	for (int i = 0; i < N / 2; ++i) {
		int temp = rand() % 800;
		xval = temp / 13.0;
		temp = rand() % 800;
		yval = temp / 13.0;
		mset.insert(Point(xval, yval));
		temp = rand() % 800;
		xval = temp / 13.0;
		temp = rand() % 800;
		yval = temp / 13.0;
		mset.emplace(Point(xval, yval));
	}
	end = std::chrono::system_clock::now();
	duration = end - start;
	std::cout << "\nc)\nIt takes " << duration.count() << " seconds to insert and emplace\n";
	
	//erase elements
	start = std::chrono::system_clock::now();
	for (int i = 0; i < N / 2; ++i) {
		mset.erase(mset.begin());
	}
	//clear elements
	mset.clear();
	//record ending time
	end = std::chrono::system_clock::now();
	//get duration
	duration = end - start;
	std::cout << "It takes " << duration.count() << " seconds to erase and clear\n";

	return 0;
}

