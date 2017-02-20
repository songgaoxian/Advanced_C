#include<iostream>
#include<string>
#include<boost/asio.hpp>
#include<memory>
#include<thread>
#include<chrono>
#include<functional>
//reset iwork
void reset(std::auto_ptr<boost::asio::io_service::work>& iwork) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	iwork.reset();
}

int main() {
	//a)create an ioservice
	boost::asio::io_service service;
	boost::system::error_code ec;
	//run service
	std::cout << "run the service\n";
	//display 0
	std::cout<<service.run(ec)<<'\n';
	if (ec) std::cout << "Error: " << ec.message() << '\n';
	//wait for 1 second
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//shut down the service
	service.stop();

	//b)create ioservice work
	boost::asio::io_service service2;
	std::auto_ptr<boost::asio::io_service::work> iwork(new boost::asio::io_service::work(service2));
	//when building large applications, io_service is expected to continue running till all work is finished
	std::cout << "start running io service:\n";
	//reset iwork within 1 second; after reset, run() stopped
	std::thread t1(&reset, iwork);
	service2.run();
	std::cout << "end running\n";
	t1.join();
	return 0;
}