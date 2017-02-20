#ifndef C_H
#define C_H
#include<boost/asio.hpp>
#include<iostream>
#include<boost/bind.hpp>

class C {
private:
	//a)create class C with counter and timer
	int counter = 0;
	boost::asio::deadline_timer dt;
public:
	//c)
	void print() {
		if (counter < 5) {
			std::cout << "dt will be called to wait with counter " << counter << '\n';
			//increment counter
			counter++;
			//reset timer
			dt.expires_from_now(boost::posix_time::seconds(3));
			//async wait
			dt.async_wait(boost::bind(&C::print,this));

		}
		else {
			std::cout << "dt is not called with counter " << counter << '\n';
		}

	}

	//b)constructor with ioservice
	C(boost::asio::io_service& ios):dt(ios,boost::posix_time::seconds(1))
	{
		//async wait for print
		dt.async_wait(boost::bind(&C::print,this));
		counter = 0;
	}
};




#endif
