#ifndef Builder_H
#define Builder_H
#include"ClassDeclaration.h"
#include "Shape.h"
#include "IODevice.h"
#include <iostream>
#include <memory>
#include<tuple>
using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;
class Builder {
public:
	std::tuple<ShapePointer, IODevicePointer>getProduct();
	virtual ShapePointer getShape() = 0;
	virtual IODevicePointer getIODevice() = 0;
};
class BuildCircleIO :public Builder {
private:
	Circle c;
	CircleIODevice IO;
public:
	BuildCircleIO(const Circle& src, const CircleIODevice& srcio);
	virtual ShapePointer getShape();
	virtual IODevicePointer getIODevice();
};
class BuildLineIO :public Builder {
private:
	Line l;
	LineIODevice IO;
public:
	BuildLineIO(const Line& src, const LineIODevice& srcio);
	virtual ShapePointer getShape();
	virtual IODevicePointer getIODevice();
};
#endif