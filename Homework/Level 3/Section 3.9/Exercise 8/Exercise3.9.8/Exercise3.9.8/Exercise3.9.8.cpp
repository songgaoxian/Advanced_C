#include"C.h"

int main() {
	//d)test class C
	boost::asio::io_service io;
	C p(io);
	io.run();
	return 0;
}