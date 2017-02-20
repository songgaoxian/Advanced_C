#include<iostream>
#include<chrono>
class StopWatch {
public:
	//default constructor
	StopWatch():isStart(false),isEnd(false){}
	//start
	void StartStopWatch() {
		start = std::chrono::system_clock::now();
		isStart = true;
	}
	//stop
	void StopStopWatch() {
		end = std::chrono::system_clock::now();
		isEnd = true;
	}
	//reset
	void Reset() {
		start = std::chrono::system_clock::now();
		isStart = false;
		end = std::chrono::system_clock::now();
		isEnd = false;
	}
	//get time
	double GetTime() const {
		double count;
		if (isStart && isEnd) {
			std::chrono::duration<double> D = end - start;
			count = D.count();
			std::cout << "The operation is measured properly\n";
		}
		else {
			std::cout << "either the start time point or the end time point is not recorded\n";
			count = -1;//it means measure error
		}
		return count;
	}
private:
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	bool isStart;//true:if start records the starting time of the operation;otherwise, false;
	bool isEnd; //true if end records the ending time of the operation; otherwise,false;
	
	//cannot be accessed from outside
	StopWatch(const StopWatch& src):start(src.start),end(src.end),isStart(src.isStart),isEnd(src.isEnd){}
	StopWatch& operator=(const StopWatch& src) {
		start = src.start;
		end = src.end;
		isStart = src.isStart;
		isEnd = src.isEnd;
	}
};

int main() {
	//test StopWatch class
	const int N = 9000;
	double arr[N];
	StopWatch swatch;
	//record start time
	swatch.StartStopWatch();
	for (int i = 0; i < N; ++i)
		arr[i] = 11.1;
	//record end time
	swatch.StopStopWatch();
	std::cout << "It takes " << swatch.GetTime() << " seconds to assign 11.1 to arr\n";
	
	//reset StopWatch
	swatch.Reset();
	//record start time
	swatch.StartStopWatch();
	for (int i = 0; i < N; ++i)
		arr[i] /= 2;
	//record end time
	swatch.StopStopWatch();
	std::cout << "It takes " << swatch.GetTime() << " seconds to modify arr\n";
	return 0;

}