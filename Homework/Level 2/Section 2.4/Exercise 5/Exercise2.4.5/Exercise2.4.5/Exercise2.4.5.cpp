#define _CRT_SECURE_NO_WARNINGS
#include "deleters.h"
#include<memory>

int main() {
	//c) test function object deleter
	 {
		//open  file in write mode
		FILE* myFile = fopen("file.txt", "w");
		//create a shared_ptr for file
		std::shared_ptr<FILE> mySharedFile(myFile, FileFinalizer());
		//write something into file
		fprintf(myFile,"why does Jesus not control me like human control machine?\n");
	}
	//end of testing function object
	//test free function deleter
	{
		//open file in write mode
		FILE* myFile = fopen("file1.txt", "w");
		//create a shared_ptr
		std::shared_ptr<FILE> mySharedFile(myFile, freeDeleter);
		//write to file
		fprintf(myFile,"why is it destined to suffer and sin for whoever tries to follow Jesus?\n");
		//no explicit fclose operation
	}
	//end of testing free function
	//test lambda deleter
	{
		//open file in write mode
		FILE* myFile = fopen("file2.txt", "w");
		//create a shared_ptr
		std::shared_ptr<FILE> mySharedFile(myFile, lambdaDelete);
		//write to file
		fprintf(myFile,"I don't mind being a machine as long as I don't sin anymore and don't suffer anymore\n");
		//no explicit fclose operation
	}
	//end of c)

	//d)
	try {
		//open a file
		FILE* f = fopen("file3.txt", "w");
		//create a shared_ptr
		std::shared_ptr<FILE> mySharedFile(f, lambdaDelete);
		//use a small loop to write to file
		for (int i = 0; i < 6; ++i) {
			fprintf(f, "hello world\n");
			//throw exception when i is 3
			if (i == 3)
				throw - 1;
		}
	}
	catch (...) {
		//open the file again
		fopen("file3.txt", "w"); //it compiles
	}
	//end of d)

	return 0;
}