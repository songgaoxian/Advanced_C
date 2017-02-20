#include<queue>
#include<boost/thread.hpp>
#include<boost/thread/mutex.hpp>
#include<iostream>
#include<chrono>
#include<vector>
//maximum number of clients in barber shop
const int N = 6;

class sQ {
private:
	boost::mutex m;
	boost::condition_variable cv;
	std::queue<int> Q;
public:
	sQ(std::queue<int>& src) :Q(src) {}
	void Enqueue(int id) {
		boost::unique_lock<boost::mutex> lck(m);
		//if Q's size is no less than N, wait
		cv.wait(lck, [&]() {return Q.size() < N; });
		//Q's size is less than N
		Q.push(id);
		//notify that the queue is non empty now
		cv.notify_one();
	}
	void Dequeue() {
		boost::unique_lock<boost::mutex> lck(m);
		//if Q is empty, wait
		cv.wait(lck, [&]() {return Q.size() > 0; });
		//Q's size is non empty
		std::cout << Q.front() << " leaves.\n";
		Q.pop();
		cv.notify_one();
	}
	int Size() {
		return Q.size();
	}
};



//producer thread
class Producer {
private:
    //point to the Queue of waiting clients
	sQ* waitingQ;
public:
	Producer(sQ* src) :waitingQ(src) {}
	
	void Client() {
		int client_id = 1;
		while (true) {
	        //every 10 seconds, a client comes
			do {
				boost::this_thread::sleep(boost::posix_time::seconds(10));
			} while (waitingQ->Size() >= N);
			waitingQ->Enqueue(client_id++);
			std::cout <<waitingQ->Size()<<" clients queue at barbershop\n";
		}
	}
};

//consumer thread
class Consumer {
private:
	sQ* waitingQ;
public:
	Consumer(sQ* src):waitingQ(src){}
	//assume the service or wake up takes 7 seconds
	void Barber() {
		while (true) {
			if (waitingQ->Size() == 0)
				std::cout << "Barber sleep...\n";
			else {
				std::cout << "\nstart service...\n";
				std::cout << "\nend service\n";
				waitingQ->Dequeue();
			}
			boost::this_thread::sleep(boost::posix_time::seconds(7));
		}
	}
};

int main() {
	std::queue<int> waitQ;
	sQ sq(waitQ);
	Producer p(&sq);
	Consumer c(&sq);

	//create threads for producer and consumer
	boost::thread tClient(&Producer::Client, p);
	boost::thread tBarber(&Consumer::Barber, c);

	//enter to stop
	getchar();

	tClient.interrupt();
	tBarber.interrupt();
	tClient.join();
	tBarber.join();
	return 0;
}
