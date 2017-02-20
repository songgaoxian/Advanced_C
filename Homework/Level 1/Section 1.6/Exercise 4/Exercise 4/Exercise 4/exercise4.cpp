#include "Client.h"
int main() {
	int n = 10; int val = 2;
	Client<int> myClient(n, val); myClient.print();
	std::cout << "new client:\n";
	newClient<int> mynewClient(n, val); mynewClient.print();
	return 0;
}