#include "IODevice.h"
void CircleIODevice::operator<<(const Circle& c) {
	std::cout << c.Circleinfo() << std::endl;
}
void CircleIODevice::operator<<(const Line& c) {
	std::cout << c.Lineinfo() << std::endl;
}
void LineIODevice::operator<<(const Line& l) {
	std::cout << l.Lineinfo() << std::endl;
}
void LineIODevice::operator<<(const Circle& l) {
	std::cout << l.Circleinfo() << std::endl;
}
