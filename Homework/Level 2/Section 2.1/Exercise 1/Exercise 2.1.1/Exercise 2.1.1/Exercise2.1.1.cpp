#include<iostream>
#include<type_traits>
#include<memory>
using std::cout;

//for part a)
//this function checks if type T is a pointer, null pointer, lvalue reference, rvalue reference
template<typename T>
void CheckType(const T& t) {
	//check if T is of pointer type and print result of checking
	if (std::is_pointer<T>::value) {
		cout << "It is pointer type\n";
	}
	else {
		cout << "not_pointer type\n";
	}
	//check if T is null pointer and print result of checking
	if (std::is_null_pointer<T>::value) {
		cout << "It is a null pointer\n";
	}
	else {
		cout << "not_null_pointer\n";
	}
	//check if T is lvalue reference and print result of checking
	if (std::is_lvalue_reference<T>::value) {
		cout << "It is lvalue reference\n";
	}
	else {
		cout << "not_lvalue_reference\n";
	}
	//check if T is rvalue reference and print result of checking
	if (std::is_rvalue_reference<T>::value) {
		cout << "It is rvalue reference\n";
	}
	else {
		cout << "not_rvalue_reference\n";
	}
}

//class A will be used for part b)
class A {
public:
	int x;
	void print() { cout << "a\n"; }
};

int main() {
	//part c) check shared pointer
	std::shared_ptr<int> sptr(new int);
	*sptr = 5;
	cout << "Check shared pointer:\n";
	CheckType(sptr);//check shared_ptr
	cout << "Check shared pointer's raw pointer:\n";
	CheckType(sptr.get()); //check the raw pointer
						   //shared pointer is not a pointer type, but is a pointer type when converted to a raw pointer
						   //end of c)
	cout << "\n";
	//test functionality of CheckType function
	cout << "Check double* ptr:\n";
	double* ptr = new double;
	*ptr = 11.1;
	CheckType(ptr);
	delete ptr;
	cout << "\n";
	cout << "Check null pointer:\n";
	CheckType(nullptr);
	cout << "\n";
	cout << "Check double* pp:\n";
	double *pp = new double;
	CheckType(pp);
	cout << "\n";
	delete pp;
	cout << "Check double& lval:\n";
	double double1 = 1.1;
	double& lval = double1;
	CheckType<double&>(lval);
	cout << "\n";
	double&& rval = 1.1;
	cout << "Check double&& rval:\n";
	CheckType<double&&>(rval);
	cout << "\n";
	//end of testing

	//for part b)
	void(A::*pointer)() = &A::print;
	cout << "is member function pointer:\n";
	//check if A* is a member function pointer
	cout << "A*:" << std::boolalpha << std::is_member_function_pointer<A*>::value << std::endl;
	//check if pointer is a member function pointer
	cout << "decltype(pointer): " << std::boolalpha << std::is_member_function_pointer<decltype(pointer)>::value << std::endl;

	cout << "\n";
	int A::*intpointer = &A::x;
	cout << "is member object pointer:\n";
	//check if intpointer is a member object pointer
	cout << "decltype(intpointer): " << std::boolalpha << std::is_member_object_pointer<decltype(intpointer)>::value << std::endl;
	//end of b)
	return 0;
}