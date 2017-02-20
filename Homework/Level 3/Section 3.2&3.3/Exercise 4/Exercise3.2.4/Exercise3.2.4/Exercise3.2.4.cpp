#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<atomic>

//for a)
std::string data; //shared data between master and worker
std::mutex m;
std::condition_variable cv; //for synchronization
//initial state of worker and master
/*std::atomic<bool> workerReady = false;
std::atomic<bool> masterReady = false;*/
//d)replace with atomic_flag
std::atomic_flag workerReady = ATOMIC_FLAG_INIT;
std::atomic_flag masterReady = ATOMIC_FLAG_INIT;

//b) worker thread
void workThread() {
	std::unique_lock<std::mutex> lck(m);
	//wait till worker is ready
	//cv.wait(lck, []() {return workerReady.load(); });
	//return false to wait
	cv.wait(lck, []() {return workerReady.test_and_set(); });
	//now ready and update data
	data += "updated by worker;";
	//notify master
	//masterReady = true;
	//set masterReady
	masterReady.test_and_set();
	cv.notify_one();
}
int main() {
	//c) master initiation
	std::cout << "initiate the master\n";
	//call worker then wait
	std::thread worker(&workThread);
	{
		std::lock_guard<std::mutex> lck(m);
		//initiate data
		data = "To be updated: ";
		//worker is ready
		//workerReady = true;//not necessary anymore
	}
	std::cout << "it is prepared for the worker to work\n";
	cv.notify_one();
	{
		std::unique_lock<std::mutex> lck(m);
		//wait for worker to finish work
		//cv.wait(lck, []() {return masterReady.load(); });
		//if workthread is finihsed, return true; else return false
		cv.wait(lck, []() {return masterReady.test_and_set(); });
	}
	worker.join();
	std::cout << "\nwork is finished and the result: " << data << std::endl;
	return 0;
}
