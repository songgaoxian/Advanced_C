#ifndef ActiveObject_H
#define ActiveObject_H
#include<iostream>
#include<thread>

class ActiveObject {
private:
	std::thread activeThread;
public:
	explicit ActiveObject(std::thread src) { 
		std::cout << "constructed\n";
		activeThread = std::move(src);	
	}
	~ActiveObject() {
		std::cout << "destructed\n";
		if (activeThread.joinable())
			activeThread.join();	
	}
};


#endif
