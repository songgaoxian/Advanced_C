#include "Shape.h"
#include<array>
#include<iostream>
template<typename T, typename... Types>
void rotate(double factor, T& arg, Types&... args) {
	arg.rotate(factor);
	rotate(factor, args...);
}

template<typename T>
void rotate(double factor, T& arg) {
	arg.rotate(factor);
}

int main() {
	Circle circle;
	Line line;
	Valve valve;
	double factor = 2.0;
	rotate(factor, circle);
	rotate(factor, circle, line);
	rotate(factor, circle, valve);
	rotate(factor * 2, circle, valve, line);
	std::cout << "another type\n";
	std::array<Shape*, 5>
		shapeList{ &circle, &line, &circle, &circle, &line };
	double factor2 = 20.0;
	for (auto& elem : shapeList) {
		elem->rotate(factor2);
	}
	//we cannot use valve in this array, because it is independent of Shape and cannot be assigned to Shape pointer
	return 0;

}