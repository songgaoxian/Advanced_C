//Exercise5.9.1
//
//test stack
//written on 2016/7/1

#include"Stack.hpp"
#include<iostream>
#include<string>

int main() {
	int size = 6;
	Stack stk(size);

	//push to stack
	int i = 1;
	while (i <= size+2) {
		try {
			//push to stk
			stk.Push(i * 2);
			++i;
		}
		catch (std::string s) { std::cout << s; ++i; }
	}
	
	//pop the stack
	i = size;
	while (i >= 0) {
		try {
			std::cout << "Pop out " << stk.Pop() << '\n';
			--i;
		}
		catch (std::string s) {
			//print out error message
			std::cout << s << '\n';
			--i;
		}
	}

	return 0;
}