#ifndef Shape_H
#define Shape_H
#include<functional>
#include<iostream>
using VoidFunctionType = std::function<void(double)>;
class Shape {
protected:
	VoidFunctionType rotate;
public:
	virtual void keepBaseABC() const = 0;
};

class Circle : public Shape {
public:
	Circle() {
		Shape::rotate = [](double d) {
			std::cout << "c\n";
		};
	}
	void rotate(double d) {		
		Shape::rotate(d);
	}
	void keepBaseABC()const override {}
};
#endif