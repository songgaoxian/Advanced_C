#ifndef IODevice_H
#define IODevice_H
#include "ClassDeclaration.h"
#include "Shape.h"
#include <iostream>
class IODevice {
public:
	virtual void operator << (const Circle& c) = 0;
	virtual void operator << (const Line& c) = 0;
};
class CircleIODevice :public IODevice {
public:
	virtual void operator<< (const Circle& c);
	virtual void operator<<(const Line& c);
};
class LineIODevice : public IODevice {
public:
	virtual void operator<< (const Line& l);
	virtual void operator<<(const Circle& l);
};
#endif
