//implement the stopwatch class

#include"Stopwatch.hpp"
#include<iostream>

void StopWatch::StartStopWatch() {
	start = std::chrono::system_clock::now();
	isStart = true;
}
void StopWatch::StopStopWatch() {
	end = std::chrono::system_clock::now();
	isEnd = true;
}
void StopWatch::Reset() {
	start = std::chrono::system_clock::now();
	isStart = false;
	end = std::chrono::system_clock::now();
	isEnd = false;
}
double StopWatch::GetTime() const {
	double count;
	if (isStart && isEnd) {
		std::chrono::duration<double> D = end - start;
		count = D.count(); //get the time
	}
	else {
		std::cout << "either the start time point or the end time point is not recorded\n";
		count = -1;//it means measure error
	}
	return count;
}