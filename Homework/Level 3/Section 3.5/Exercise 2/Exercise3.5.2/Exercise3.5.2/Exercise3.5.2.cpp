#include<iostream>
#include<functional>
#include<boost/thread.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<queue>
//copied
using FunctionType = std::function<double(double)>;
class Command {
private:
	long ID; //priority of command
	FunctionType algo;
public:
	Command() {}
	Command(const FunctionType& algorithm, long priority) :algo(algorithm), ID(priority) {}
	void Execute(double x) {
		boost::this_thread::sleep(boost::posix_time::millisec(5000));
		std::cout << algo(x) << '\n';
	}
	int priority() const { return ID; }
};
//a) comparator for command
struct Comparator {
	Comparator() {}
	bool operator()(const Command& c1, const Command& c2) {
		return c1.priority() < c2.priority();
	}
};
//b)
//create the following algos for instance of command
double algo1(double x) { return x + 99; }
double algo2(double x) { return x*x; }
double algo3(double x) { return x / 3.1; }

int main() {
	long ID1 = 55;
	long ID2 = 22;
	long ID3 = 99;
	//construct instances of Command
	Command c1(algo1, ID1);
	Command c2(algo2, ID2);
	Command c3(algo3, ID3);
	//c) create priority queue
	std::priority_queue<Command, std::vector<Command>, Comparator> pQueue;
	//insert b) objects
	pQueue.push(c1);
	pQueue.push(c2);
	pQueue.push(c3);
	double x = 4.5;
	//d)execute each command in priority queue
	Command temp;
	while (!pQueue.empty()) {
		temp = pQueue.top();
		std::cout << "Priority of current command: " << temp.priority() << std::endl;
		temp.Execute(x);
		pQueue.pop();
	}
	return 0;
}
