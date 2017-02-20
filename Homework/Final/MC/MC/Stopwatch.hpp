//declare the stopwatch class

#ifndef StopWatch_HPP
#define StopWatch_HPP
#include<chrono>

class StopWatch {
private:
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	bool isStart;//true:if start records the starting time of the operation;otherwise, false;
	bool isEnd; //true if end records the ending time of the operation; otherwise,false;

	//cannot be accessed from outside
	StopWatch(const StopWatch& src) :start(src.start), end(src.end), isStart(src.isStart), isEnd(src.isEnd) {}
	StopWatch& operator=(const StopWatch& src) { return *this; }
public:
	//default constructor
	StopWatch() :isStart(false), isEnd(false) {}
	//start
	void StartStopWatch();
	//stop
	void StopStopWatch();
	//reset
	void Reset();
	//get time
	double GetTime() const;
};



#endif