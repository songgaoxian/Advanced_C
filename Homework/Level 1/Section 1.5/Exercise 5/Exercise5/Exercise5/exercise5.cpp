#include "Builder.h"

int main() {
	Circle c(1.0, 2.1, 3.0);
	Line l(1.0, 1.0, 2.0, 2.0);
	CircleIODevice ioc;
	LineIODevice iol;
	c.display(ioc);
	c.display(iol);
	BuildLineIO blio(l, iol);
	auto result = blio.getProduct();
	ShapePointer shp;
	IODevicePointer iop;
	std::tie(shp, iop) = result;
	(*shp).display(*iop);
	return 0;
}