//DVM_Imp.cpp
//Implement DVM_Imp.hpp

#include"DVM_Imp.hpp"

std::string Source::message(){
	std::cout << "Choose a product: Orange or Cola?";
	std::string product;
	//get product choice
	std::cin >> product;
	return product;
}
int Auth::amount() { return money; }
void Auth::increment(int amount) { money += amount; }
void Auth::decrement(int amount) { money -= amount; }

Resource::Resource() {
	std::tuple<int, int> tup(2, 10);
	drinks.insert(std::pair<std::string, Product>("Cola", tup));

	std::tuple<int, int> tup2(2, 20);
	drinks.insert(std::pair<std::string, Product>("Orange", tup2));
}
void Resource::displayProducts() {
	std::cout << "****Product Database*****\n";
	for (auto it = drinks.begin(); it != drinks.end(); it++) {
		std::cout << it->first << ": price=" << std::get<0>(it->second) << ", supply=" << std::get<1>(it->second) << "\n";
	}
	std::cout << "**************\n";
}
Product Resource::getProduct(std::string name) {
	auto prod = drinks.find(name);
	if (prod != drinks.end()) { return prod->second; }
	throw std::string("no such product");
}
void Resource::updateProduct(std::string name, int quantity) {
	auto prod = drinks.find(name);
	if (prod != drinks.end()) { 
		std::get<1>(prod->second) -= quantity; 
	}
}
void Sink::notify(std::string prod, bool status) {
	std::cout << "Transaction " << prod << ", status " << std::boolalpha << status << '\n';
}
//initialize transaction status
MIS::MIS() { 
	inprocess = true; 
	complete = false;
}
//when transaction is finished, MIS is notified
void MIS::notify() {
	inprocess = false;
	complete = true;
	std::boolalpha(std::cout);
	std::cout << "Transaction in process?" << inprocess << "\n";
	std::cout << "Transaction complete?" << complete << "\n";
}
DVM::DVM(Source& iso, Auth& ia, Resource& ir, Sink& isi, MIS& im):iso_(iso),ia_(ia),ir_(ir),isi_(isi),im_(im){}

void DVM::run() {
	//display available resource
	ir_.displayProducts();
	
	//get choice of product
	std::string product = iso_.message();
	
	//get product info
	Product info;
	try {
		info = ir_.getProduct(product);
	}
	catch (std::string err) {
		std::cout << err; //display error message
		return;
	}
	
	//The following codes are executed only if a valid product is chosen
	std::cout << "How many do you wants?\n";
	int num;
	std::cin >> num;
	int supply = std::get<1>(info);
	//check if there are enough products
	if (supply < num) {
		std::cout << "Not enough stock\n";
		return;
	}
	
	//if enough stock, codes will be executed further
	std::cout << "Insert your coins\n";
	int amt;
	std::cin >> amt;
	ia_.increment(amt);
	std::cout << "You inserted " << ia_.amount() << '\n';

	//check if enough coins inserted
	int required = num*std::get<0>(info);
	if (amt < required) {
		std::cout << "Not enough coins\n";
		return;
	}
	//the following codes will be executed only if enough coins inserted
	int change = amt - required;
    
	//commit transaction
	ir_.updateProduct(product, num);
	//give you the change
	ia_.decrement(change);
	std::cout << "Accept your change=" << change << '\n';
	std::cout << "The updated list of products:\n";
	ir_.displayProducts();

	//notify Sink and MIS
	isi_.notify(product, true);
	im_.notify();
}