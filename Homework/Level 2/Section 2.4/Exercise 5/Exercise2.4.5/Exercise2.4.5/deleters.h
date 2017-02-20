#ifndef Deleters_H
#define Deleters_H
#include<stdio.h>
#include<iostream>
#include<functional>

using std::cout;

//for a)
//this object is to act as deleter
struct FileFinalizer {
	void operator()(FILE* f) {
		//close the file and display close operation message
		if (f != NULL) {
			fclose(f);
		}
			cout << "close file by function object\n";
	}
};
//end of a)

//for b)
//this free function is a custom deleter
void freeDeleter(FILE* f) {
	//close the file and display operation message
	if (f != NULL) {
		fclose(f);
	}
	cout << "close file by free function\n";
}
//this lambda function is a custom deleter
auto lambdaDelete = [](FILE* f) {
	//close the file and display operation message
	if (f != NULL) {
		fclose(f);
	}
	cout << "close file by lambda function\n";
};
//end of b)

#endif