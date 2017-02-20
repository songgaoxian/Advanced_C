#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/asio.hpp>
#include<iostream>
//handler for timer1
void Handler1(const boost::system::error_code& ec) {
	std::cout << "Timer 1's handler:\n";
	if (ec) std::cout << ec.message() << '\n';
	std::cout << "The End\n";
}
//handler for timer2
void Handler2(const boost::system::error_code& ec) {
	std::cout << "Timer 2's handler:\n";
	if (ec) std::cout << ec.message() << '\n';
	std::cout << "The End\n";
}

int main() {
	//a)create ioservice
	boost::asio::io_service serv1;
	//create one timer1 which will expire after 5 second
	boost::asio::deadline_timer timer1(serv1);
	std::cout << "a)\nTimer 1 created.\n";
	//set expire time
	timer1.expires_from_now(boost::posix_time::seconds(5));

	//create another timer which will expire at an absolute time
	boost::asio::deadline_timer timer2(serv1);
	std::cout << "Timer 2 created.\n";
	//set expire time
	timer2.expires_at(timer1.expires_at()-boost::posix_time::seconds(3));

	//b)
	std::cout << "\nUse timers synchronously:\n";
	std::cout << "Timer 1 waits synchronously:\n";
	//timer1 waits synchronously
	timer1.wait();
	std::cout << "Timer 1 exits waiting\n";

	std::cout << "\nTimer 2 waits synchronously:\n";
	//timer2 waits sync
	timer2.wait();
	std::cout << "Timer 2 exists waiting\n";

	std::cout << "\nUse timers asynchronously:\n";
	//set expire time 
	timer1.expires_from_now(boost::posix_time::seconds(4));
	//timer1 waits asynchronously
	std::cout << "Timer 1 waits async:\n";
	timer1.async_wait(&Handler1);

	//timer2 waits async
	std::cout << "Timer 2 waits async:\n";
	//set expire time
	timer2.expires_at(timer1.expires_at() - boost::posix_time::seconds(2));
	timer2.async_wait(&Handler2);

	//for all async processes to be finished
	serv1.run();
	std::cout << "All asynchronous operations finished\n";


	return 0;


}