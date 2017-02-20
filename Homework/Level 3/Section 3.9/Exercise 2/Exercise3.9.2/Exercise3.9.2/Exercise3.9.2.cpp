#include<iostream>
#include<boost/asio.hpp>
#include<boost/thread/thread.hpp>
#include<functional>

void Fib(std::size_t);

//a)create WorkerThread function
void WorkerThread(boost::asio::io_service& iserve) {
	iserve.run();
}

void StopIO(boost::asio::io_service::work& iwork) {
	boost::this_thread::sleep(boost::posix_time::seconds(5));
	//signal that work is finished
	iwork.~work();
}

//b)recursive function to compute Fibonacci
std::size_t GetFib(std::size_t n) {
	//end of recursive
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (n == 2) return 1;
	//recursively call GetFib
	return GetFib(n - 1) + GetFib(n - 2);
}
//display Fib number
void Fib(std::size_t n) {
	std::size_t result = GetFib(n);
	std::cout << n << ": " << result << '\n';
}

int main() {
	//c)create ioservice instance
	boost::asio::io_service serve;
	//corresponding work object
	boost::asio::io_service::work iwork(serve);
	//d)create a thread group
	boost::thread_group thread_g;
	int N = 4;
	for(int i=0;i<N;++i)
	    thread_g.create_thread(std::bind(WorkerThread,std::ref(serve)));
	//e)calculate Fibonacci for the following numbers
	for(int n=3;n<=6;++n){
		serve.post(boost::bind(Fib, n));
	}
	//stop run()
	boost::thread(&StopIO, iwork);

	thread_g.join_all();
	return 0;

}