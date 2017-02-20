#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/asio.hpp>
#include<boost/asio/steady_timer.hpp>
#include<boost/asio/high_resolution_timer.hpp>
#include<boost/asio/system_timer.hpp>
#include<iostream>
#include<string>
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
	//for steady_timers
	//create ioservice
	boost::asio::io_service serv1;
	//create one timer1 which expires after some period of time
	boost::asio::steady_timer timer1(serv1);
	//create another timer which will expire at an absolute time
	boost::asio::steady_timer timer2(serv1);
	std::string s("steady_timers");
	std::cout << s << "\n";
	//set expire time
	timer1.expires_from_now(std::chrono::seconds(4));
	//set expire time
	timer2.expires_at(timer1.expires_at() + std::chrono::seconds(1));

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
	timer1.expires_from_now(std::chrono::seconds(4));
	//timer1 waits asynchronously
	std::cout << "Timer 1 waits async:\n";
	timer1.async_wait(&Handler1);

	//timer2 waits async
	std::cout << "Timer 2 waits async:\n";
	//set expire time
	timer2.expires_at(timer1.expires_at() - std::chrono::nanoseconds(500));
	timer2.async_wait(&Handler2);

	//for all async processes to be finished
	serv1.run();
	std::cout << "All asynchronous operations are finished for " << s << "\n";
	std::cout << "\n\n";
	serv1.stop();



	//for high_resolution_timers
	boost::asio::io_service serv2;
	//create two timers
	boost::asio::high_resolution_timer t1(serv2);
	boost::asio::high_resolution_timer t2(serv2);
	s="high_resolution_timers";
	std::cout << s << "\n";
	//set expire time
	t1.expires_from_now(std::chrono::seconds(4));
	//set expire time
	t2.expires_at(t1.expires_at() + std::chrono::nanoseconds(2000));

	std::cout << "\nUse timers synchronously:\n";
	std::cout << "t1 waits synchronously:\n";
	//t1 waits synchronously
	t1.wait();
	std::cout << "t1 exits waiting\n";

	std::cout << "\nt2 waits synchronously:\n";
	//t2 waits sync
	t2.wait();
	std::cout << "t2 exists waiting\n";

	std::cout << "\nUse timers asynchronously:\n";
	//set expire time 
	t1.expires_from_now(std::chrono::seconds(3));
	//t1 waits asynchronously
	std::cout << "t1 waits async:\n";
	t1.async_wait(&Handler1);

	//t2 waits async
	std::cout << "t2 waits async:\n";
	//set expire time
	t2.expires_at(timer1.expires_at() - std::chrono::nanoseconds(500));
	t2.async_wait(&Handler2);

	//for all async processes to be finished
	serv2.run();
	std::cout << "All asynchronous operations are finished for " << s << "\n";
	std::cout << "\n\n";
  
	//for system_timer
	boost::asio::io_service serv3;
	//create two timers
	boost::asio::system_timer s1(serv3);
	boost::asio::system_timer s2(serv3);
	s = "system_timers";
	std::cout << s << "\n";
	//set expire time
	s1.expires_from_now(std::chrono::duration<int>(4));
	//set expire time
	s2.expires_at(s1.expires_at() + std::chrono::duration<int>(2));
	
	std::cout << "\nUse timers synchronously:\n";
	std::cout << "s1 waits synchronously:\n";
	//s1 waits synchronously
	s1.wait();
	std::cout << "s1 exits waiting\n";

	std::cout << "\ns2 waits synchronously:\n";
	//s2 waits sync
	s2.wait();
	std::cout << "s2 exists waiting\n";
	
	std::cout << "\nUse timers asynchronously:\n";
	//set expire time 
	s1.expires_from_now(std::chrono::duration<int>(4));
	//s1 waits asynchronously
	std::cout << "s1 waits async:\n";
	s1.async_wait(&Handler1);

	//s2 waits async
	std::cout << "s2 waits async:\n";
	//set expire time
	s2.expires_at(s1.expires_at() - std::chrono::duration<int>(2));
	s2.async_wait(&Handler2);

	//for all async processes to be finished
	serv3.run();
	std::cout << "All asynchronous operations are finished for " << s << "\n";
	
	return 0;


}