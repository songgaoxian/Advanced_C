#include<iostream>
#include<future>
#include<thread>
#include<random>
#include<chrono>
#include<math.h>
#include<queue>
//copied
double compute(double x, double y) {
	std::default_random_engine dre(42);
	std::uniform_int_distribution<int> delay(0, 1000);
	std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));
	return std::cos(x)*std::exp(y);
}
int main() {
	double x = 0.0; double y = 2.71;
	std::future<double> fut = std::async(compute, x, y);
	double result = fut.get();
	std::cout << "Result: " << result << '\n';
	//b) use packed_task
	std::packaged_task<double(double, double)> task(compute);
	auto fut2 = task.get_future();
	//start task
	task(x,y);
	//wait task to finish and process result
	std::cout << "Result: " << fut2.get() << std::endl;

	//c)
	using pTask = std::packaged_task<double(double, double)>;
	//create a queue of packaged tasks
	std::queue<pTask> taskQ;
	for (int i = 0; i < 3; ++i)
		taskQ.push(pTask(compute));
	pTask temp;
	std::future<double> temp_f;
	//deque each task and execute it
	for (int i = 0; i < 3; ++i) {
		temp = std::move(taskQ.front());
		temp_f = std::move(temp.get_future());
		taskQ.pop();
		//start taks
		temp(x, y);
		std::cout << "Result of queue: " << temp_f.get() << std::endl;
	}

	return 0;

}