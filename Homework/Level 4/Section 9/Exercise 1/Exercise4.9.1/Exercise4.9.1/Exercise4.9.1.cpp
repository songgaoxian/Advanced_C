//Exercise 4.9.1
//
//exercises to create and use signals and slots
//written on 2016/06/23

#include"Slots.h"
#include"Struct.h"
#include<functional>
	

int main() {
	//a)
	std::cout << "a)\n";
	//create a signal
	boost::signals2::signal<void()> signal;
	//connect signal to lambda
	signal.connect(slot1);
	//connect to free function
	signal.connect(slot2);
    //create function object
	slot3 s3;
	//connect to function object
	signal.connect(s3);
	//emit signal
	signal();

	//b)
	std::cout << "\nb)\n";
	double val = 1.2;
	//create MyStruct object
	MyStruct sct(val);
	std::function<void()> slot4 = boost::bind(&MyStruct::modify, sct, val);
	//connect to signal
	signal.connect(slot4);
    //emit signal
	signal();

	//c)
	std::cout << "\nb)\n";
	//disconnect free function
	signal.disconnect(&slot2);
	std::cout << "\nAfter disconnect slot2:\n";
	signal();

	//disconnect all
	signal.disconnect_all_slots();
	std::cout << "\nAfter disconnect all other slots:\n";
	signal();
	std::cout << '\n';


	//d)
	std::cout << "\nd)\n";
	//create signal A
	boost::signals2::signal<void()> A;
	//create signal B
	boost::signals2::signal<void()> B;
	//create signal C
	boost::signals2::signal<void()> C;
	//create signal D
	boost::signals2::signal<void()> D;

	//connect B to A
	auto cAB=A.connect(B);
	auto cBC=B.connect(C);
	auto cCD=C.connect(D);
	auto cBS1=B.connect(&S1);
	auto cCS2=C.connect(&S2);
	auto cDS3=D.connect(&S3);
	auto cDS4=D.connect(&S4);
	//emit signals
	std::cout << "Emit signal A:\n";
	A();
	std::cout << "\nEmit signal B:\n";
	B();
	std::cout << "\nEmit signal C:\n";
	C();
	std::cout << "\nEmit signal D:\n";
	D();

	//disconnect signalC from B which is possible to do
	cBC.disconnect();
	std::cout << "After disconnect, emit signal B:\n";
	B();
	std::cout << "After disconnect, emit signal C:\n";
	C();
	
	return 0;
}
