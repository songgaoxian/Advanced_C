//Exercise5.5.1
//
//test Account classes under proxy pattern
//written on 2016/6/30

#include"Account.hpp"
#include"Exception.hpp"

int main() {
	//j)test Account and ProtectedAccount
	double bal = 1000;
	std::string psw = "19910514";
	Account* acct = new ProtectedAccount(bal, psw);
	try {
		//withdraw 500
		acct->Withdraw(500);
		//try to use correct and incorrect passwords
		std::cout << "After withdraw 500, balance=" << acct->GetBalance() << '\n';
	}
	catch (Exception& e) {
	}

	try {
		//withdraw 600
		acct->Withdraw(600);//funds not enough
		std::cout << "After withdraw 600, balance=" << acct->GetBalance() << '\n';
	}
	catch (Exception& e) {
	}
	return 0;

}