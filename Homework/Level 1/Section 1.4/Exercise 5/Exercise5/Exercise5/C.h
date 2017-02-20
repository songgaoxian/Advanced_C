#ifndef C_H
#define C_H
#include<iostream>
#include<functional>
#include<string>
using VoidFunctionType = std::function<void(double)>;
/* original class hierarchy
class Shape {
public:
	virtual void rotate(double d) = 0;
};
class Circle : public Shape {
public:
	void rotate(double d) override { std::cout << "c\n"; }
};
class Square : public Shape {
public:
	void rotate(double d) override { std::cout << "s\n"; }
};
*/
class Shape {
private:
	VoidFunctionType fr;
	std::string shapeType;
public:
	Shape() {
		shapeType = "s";
		std::string str = shapeType;
		fr = [=](double d) {std::cout << str<<std::endl; };
	}
	Shape(std::string src):shapeType(src){
		fr = [=](double d) {std::cout << src << std::endl; };
	}
	void rotate(double d) {
		fr(d);
	}
	
};
#endif