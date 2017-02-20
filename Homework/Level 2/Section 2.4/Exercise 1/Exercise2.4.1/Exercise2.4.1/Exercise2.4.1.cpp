#include<iostream>
#include<memory>
#include"Point.h"

//for d)
template<typename T>
using uptr = std::unique_ptr<T>;

int main() {
	//for part a)
	try 
	{
		double* d = new double(1.0);
		Point* pt = new Point(1.0, 2.0); //two-d Point class
		throw - 1;
		//dereference and call member functions
		*d = 2.0;
		(*pt).X(3.0); //modify x
		(*pt).Y(3.0); //modify y

		//can use operators for pointer operations
		pt->X(3.0); //modify x
		pt->Y(3.0); //modify y

		//explicitly clean up memory
		delete d;
		delete pt;
	}
	catch (...) {
		std::cout << "it results in memory leak\n";
		//if memory is released, destructor of pt should be called and display bye message
	}
	//end of part a)

	//for part b)
	try {
		//std::unique_ptr<double> d(new double(1.0));
		uptr<double> d(new double(1.0));
		//std::unique_ptr<Point> pt(new Point(1.0, 2.0));
		uptr<Point> pt(new Point(1.0, 2.0));
		//memory allocate dot unique pointers will be released automatically
		//no memory leaks will happen
		throw - 1;
		//dereference and call member functions
		*d = 2.0;
		(*pt).X(3.0);
		(*pt).Y(3.0);

		//can use pointer operations
		pt->X(3.0);
		pt->Y(3.0);
		//no need for delete
	}
	catch (...) {
		std::cout << "no memory leak\n";
		//destructor of point is called meaning that there is no memory leak
	}
	//end of part b)

	
		//for part c)

        
		double* d4 = new double(1.5);

		//initialize two unique pointers to same pointer
		//std::unique_ptr<double> pt1(d4);
		uptr<double> pt1(d4);
		//std::unique_ptr<double> pt2(d4); //cannot run this statement properly
	

		//assign one unique pointer to another
		//std::unique_ptr<double> pt3;
		uptr<double> pt3;
		pt3 = std::move(pt1);
		*pt3 = 2.2;
		
		
		//transfer ownership between two unique pointers
		//std::unique_ptr<double> ptTemp;
		uptr<double> ptTemp;
		//declare and initialize pointers to transfer ownership
		//std::unique_ptr<double> ptTransfer1(new double(1.0));
		uptr<double> ptTransfer1(new double(1.0));
		//std::unique_ptr<double> ptTransfer2(new double(2.0));
		uptr<double> ptTransfer2(new double(2.0));
		//transfer ownership from ptTransfer1 to ptTemp
		ptTemp = std::move(ptTransfer1);
		//transfer ownership from ptTransfer2 to ptTransfer1
		ptTransfer1 = std::move(ptTransfer2);
		//transfer ownership from ptTemp to ptTransfer2
		ptTransfer2 = std::move(ptTemp);

		//print contents after transfer
		std::cout << "*ptTransfer1: " << *ptTransfer1 << "; *ptTransfer2: " << *ptTransfer2 << std::endl;
		//end of c)
		
	
	return 0;
}