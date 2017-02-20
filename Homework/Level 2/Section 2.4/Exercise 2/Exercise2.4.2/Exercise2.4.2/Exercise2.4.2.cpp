#include "C.h"

int main() {
	/*
	//for b)
	//declare and initialize shared_ptr
	std::shared_ptr<double> d(new double(2.2));
	{	//display initial use count of d
		cout << "Use ccount: ";
		cout << d.use_count() << std::endl;
		//create instance of C1 with d
		C1 object1(d);
		object1.print();
		cout << "\nUse count: ";
		cout<<d.use_count()<<std::endl;
		{
			//create instance of C2 with d
			C2 object2(d);
			object2.print();
			cout << "\nUse count: ";
			cout << d.use_count() << std::endl;
		}
		//display the use count for ccomparison
		cout << "\nUse count outside inner scope: ";
		cout << d.use_count() << std::endl;
	}
	cout << d.use_count() << std::endl;
	//end of b)
	*/

	//for c)
	//declare and initialize shared_ptr
	std::shared_ptr<Point> p(new Point(1.1,2.2));
	{	//display initial use count of d
		cout << "Use ccount: ";
		cout << p.use_count() << std::endl;
		//create instance of C1 with d
		C1 object1(p);
		object1.print();
		cout << "\nUse count: ";
		cout << p.use_count() << std::endl;
		{
			//create instance of C2 with d
			C2 object2(p);
			object2.print();
			cout << "\nUse count: ";
			cout << p.use_count() << std::endl;
		}
		//display the use count for ccomparison
		cout << "\nUse count outside inner scope: ";
		cout << p.use_count() << std::endl;
	}
	cout << p.use_count() << std::endl;
	//end of c)

	//for d)
	//declare and initialize shared pointer
	std::shared_ptr<int> sp1(new int(6));

	//copy sp1 to spCopy
	std::shared_ptr<int> spCopy(sp1);

	//assign sp1 to spAssign
	std::shared_ptr<int> spAssign = sp1;

	//create sp2 
	std::shared_ptr<int> sp2(new int(15));

	//compare sp1 and sp2
	if (sp1 == sp2) {
		cout << "sp1 equals to spw\n";
	}
	else if (sp1 < sp2) {
		cout << "sp1 is less than sp2\n";
	}
	else if (sp1 > sp2) {
		cout << "sp1 is greater than sp2\n";
	}

	//check if the shared pointer is the only owner
	cout << "is sp2 unique? " << sp2.unique() << std::endl;
	cout << "is sp1 unique? " << sp1.unique() << std::endl;

	//display value before swap
	cout << "before swap: *sp1=" << *sp1 << "; *sp2=" << *sp2 << std::endl;
    //do the swap
	std::swap(sp1, sp2);
	//display value after swap
	cout << "after swap: *sp1=" << *sp1 << "; *sp2=" << *sp2 << std::endl;

	//create spMid for ownership transferring
	std::shared_ptr<int> spMid = std::move(sp2);
	//transfer ownership from sp1 to sp2
	sp2 = std::move(sp1);
	//transfer ownership from spMid to sp1
	sp1 = std::move(spMid);

	//reinitialize shared_ptr as empty
	sp1.reset();
	if (sp1 == 0) {
		cout << "after reset, the shared_ptr is empty\n";
	}
	else {
		cout << "still not empty\n";
	}
	//end of d)
	return 0;
}