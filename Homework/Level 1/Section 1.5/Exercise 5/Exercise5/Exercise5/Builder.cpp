#include "Builder.h"
std::tuple<ShapePointer, IODevicePointer> Builder::getProduct() {
	return std::make_tuple(getShape(), getIODevice());
}
BuildCircleIO::BuildCircleIO(const Circle& src, const CircleIODevice& srcio) {
	c = src;
	IO = srcio;
}
ShapePointer BuildCircleIO::getShape() {
	return std::make_shared<Circle>(c);
}
IODevicePointer BuildCircleIO::getIODevice() {
	return std::make_shared<CircleIODevice>(IO);
}
BuildLineIO::BuildLineIO(const Line& src, const LineIODevice& srcio) {
	l = src;
	IO = srcio;
}
ShapePointer BuildLineIO::getShape() {
	return std::make_shared<Line>(l);
}
IODevicePointer BuildLineIO::getIODevice() {
	return std::make_shared<LineIODevice>(IO);
}
