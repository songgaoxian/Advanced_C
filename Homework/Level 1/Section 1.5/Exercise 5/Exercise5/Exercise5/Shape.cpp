#include "Shape.h"
Circle::Circle(double x, double y, double r) {
	coordinateX = x;
	coordinateY = y;
	radius = r;
}
void Circle::display(IODevice& circleIO) const {
	circleIO.operator<<(*this);
}
std::string Circle::Circleinfo() const {
	return "Circle with Radius " + std::to_string(radius);
}
Line::Line(double x1, double y1, double x2, double y2) {
	xStartPoint = x1;
	yStartPoint = y1;
	xEndPoint = x2;
	yEndPoint = y2;
}
void Line::display(IODevice& lineIO) const {
	lineIO.operator<<(*this);
}
std::string Line::Lineinfo() const {
	return "Line start at (" + std::to_string(xStartPoint) + ", " + std::to_string(yStartPoint) + ")";
}
