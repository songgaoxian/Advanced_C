#include<iostream>
#include<type_traits>
#include<complex>
#include "A.h"
#include"TypeDef.h"

//this function converts input of type T to corresponding unsigned type
template<typename T>
UnsignedType<T> convertToUnsigned(const T& input) {
	if (std::is_unsigned<T>::value) {
		return input;
		//if it is already an unsigned type, just return input
	}
	else {
		return static_cast<UnsignedType<T>>(input);
		//conversion is done here
	}
}

//this function converts input of type T to corresponding signed type
template<typename T>
SignedType<T> convertToSigned(const T& input) {
	if (std::is_signed<T>::value) {
		return input;
		//if it is already a signed type, just return input
	}
	else {
		return static_cast<SignedType<T>>(input);
		//conversion is done here
	}
}

//this function converts input of type T to corresponding const type
template<typename T>
ConstType<T> convertToConst(T& input) {
	if (std::is_const<T>::value) {
		return input;
		//if it is already a const type, just return input
	}
	else {
		return static_cast<ConstType<T>>(input);
		//conversion is done here
	}
}

//this function converts input of type T to corresponding non const type
template<typename T>
NonConstType<T> convertToNonConst(T& input) {
	if (std::is_const<T>::value) {
		return static_cast<NonConstType<T>>(input);
		//if it is const, we convert it here
	}
	else {
		return input;
		//otherwise, just return the non const input
	}
}

//this function adds the pointer to input of type T
template<typename T>
PointerType<T> convertToPointer(T& input) {
	return &input;
	//we convert input to a pointer pointing to input
}

//this function assumes that only nonpointer type argument is given
//it removes the pointer of input of type T
template<typename T>
NonPointerType<T> convertToNonPointer(T& input) {
	return *input;
	// we convert input to the value that input points to
}

//this function converts input of type T to corresponding volatile type
template<typename T>
VolatileType<T> convertToVolatile(T& input) {
	if (std::is_volatile<T>::value) {
		return input;
		//if input is already volatile, just return it
	}
	else {
		return static_cast<VolatileType<T>>(input);
		//conversion is done here
	}
}

//this function converts input of type T to corresponding nonvolatile type
template<typename T>
NonVolatileType<T> convertToNonVolatile(T& input) {
	if (std::is_volatile<T>::value) {
		return static_cast<NonVolatileType<T>>(input);
		//if the input is volatile, we convert it to nonvolatile
	}
	else {
		return input;
		//otherwise, just return it
	}
}

int main() {
	//test for scalar
	const long slong = 10;
	unsigned int ulong = 1200;
	//test the functionality of converting to and from unsigned and signed
	std::cout << "convertToUnsigned(slong):  " << typeid(decltype(convertToUnsigned(slong))).name() << std::endl;
	std::cout << "convertToSigned(ulong): " << typeid(decltype(convertToSigned(ulong))).name() << std::endl;
	//test the functionality of converting to and from const and nonconst
	std::cout << "convertToConst(ulong): is const? " << std::boolalpha << std::is_const<decltype(convertToConst(ulong))>::value << std::endl;
	std::cout << "convertToNonConst(slong); is const? " << std::boolalpha << std::is_const<decltype(convertToNonConst(slong))>::value << std::endl;
	//test the functionality of converting to pointer
	std::cout << "convertToPointer(ulong): " << typeid(decltype(convertToPointer(ulong))).name() << std::endl;
	//test the functionality of converting to volatile
	std::cout << "convertToVolatile(slong): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToVolatile(slong))>::value << std::endl;

	//test for compound
	std::complex<double> cdouble1(1.1, 2.2);
	const std::complex<double> cdouble2(1.2, 2.3);
	volatile std::complex<double> vcdouble(1.2, 2.2);
	std::complex<int>* pointerc = new std::complex<int>;
	*pointerc = std::complex<int>(1, 2);
	//test the functionality of converting to and from const and nonconst
	std::cout << "convertToConst(cdouble1): is const? " << std::boolalpha << std::is_const<decltype(convertToConst(cdouble1))>::value << std::endl;
	std::cout << "convertToNonConst(cdouble2); is const? " << std::boolalpha << std::is_const<decltype(convertToNonConst(cdouble2))>::value << std::endl;
	//test the functionality of converting to and from pointer and the value pointed to
	std::cout << "convertToNonPointer(pointerc): " << typeid(decltype(convertToNonPointer(pointerc))).name() << std::endl;
	std::cout << "convertToPointer(cdouble1): " << typeid(decltype(convertToPointer(cdouble1))).name() << std::endl;
	//test the functionality of converting to and from volatilie and nonvolatile
	std::cout << "convertToVolatile(cdouble1): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToVolatile(cdouble1))>::value << std::endl;
	std::cout << "convertToNonVolatile(vcdouble): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToNonVolatile(vcdouble))>::value << std::endl;

	//test for numeric
	double* dpt = new double;
	float f = 1.4l;
	const float constf = 1.5;
	volatile double vdouble = 1.2;
	*dpt = 1.2;
	//test the functionality of converting to and from const and nonconst
	std::cout << "convertToConst(f): is const? " << std::boolalpha << std::is_const<decltype(convertToConst(f))>::value << std::endl;
	std::cout << "convertToNonConst(constf); is const? " << std::boolalpha << std::is_const<decltype(convertToNonConst(constf))>::value << std::endl;
	//test the functionality of converting to and from pointer and the value pointed to
	std::cout << "convertToNonPointer(dpt): " << typeid(decltype(convertToNonPointer(dpt))).name() << std::endl;
	std::cout << "convertToPointer(f): " << typeid(decltype(convertToPointer(f))).name() << std::endl;
	//test the functionality of converting to and from volatilie and nonvolatile
	std::cout << "convertToVolatile(f): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToVolatile(f))>::value << std::endl;
	std::cout << "convertToNonVolatile(vdouble): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToNonVolatile(vdouble))>::value << std::endl;

	//test for object
	volatile A a1;
	A a2;
	const A a3;
	A* a4 = &a2;
	//test the functionality of converting to and from const and nonconst
	std::cout << "convertToConst(a2): is const? " << std::boolalpha << std::is_const<decltype(convertToConst(a2))>::value << std::endl;
	std::cout << "convertToNonConst(a3); is const? " << std::boolalpha << std::is_const<decltype(convertToNonConst(a3))>::value << std::endl;
	//test the functionality of converting to and from pointer and the value pointed to
	std::cout << "convertToNonPointer(a4): " << typeid(decltype(convertToNonPointer(a4))).name() << std::endl;
	std::cout << "convertToPointer(a2): " << typeid(decltype(convertToPointer(a2))).name() << std::endl;
	//test the functionality of converting to and from volatilie and nonvolatile
	std::cout << "convertToVolatile(a2): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToVolatile(a2))>::value << std::endl;
	std::cout << "convertToNonVolatile(a1): is volatile?" << std::boolalpha << std::is_volatile<decltype(convertToNonVolatile(a1))>::value << std::endl;

	delete dpt;
	delete pointerc;

	return 0;
}