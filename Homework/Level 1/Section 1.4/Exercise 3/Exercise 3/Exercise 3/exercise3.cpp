#include<functional>
#include<iostream>
#include "C.h"
using namespace std;
using namespace std::placeholders;

template<typename T>
using FunctionType = function<T(const T& t)>;

int main() {
	const double m_data = 10.1;
	const double factor2 = 2.2;
	const double factor1 = 1.3;
	const double factor = 5.5;
	const double x = 9.9;
	C cobj(m_data);
	FunctionType<double> fSquare = bind(&C::Square, _1);
	FunctionType<double> fBracket = bind(&C::operator(), cobj, _1);
	FunctionType<double> fTranslate = bind(&C::translate, cobj, _1);
	FunctionType<double> fTranslate1 = bind(&C::translate2, cobj, _1, factor2);
	FunctionType<double> fTranslate2 = bind(&C::translate2, cobj, factor1, _1);
	cout << "Without binding: \n";
	cout << "Square: " << cobj.Square(x) << "; operator(): " << cobj(factor) << "; translate: " << cobj.translate(factor) << "; translate2: " << cobj.translate2(factor1, factor2) << endl;
	cout << "Binding: \n";
	cout << "Square: " << fSquare(x) << "; operator(): " << fBracket(factor) << "; translate: " << fTranslate(factor) << "; translate2: " << fTranslate1(factor1) << ":" << fTranslate2(factor2) << endl;
	return 0;
}