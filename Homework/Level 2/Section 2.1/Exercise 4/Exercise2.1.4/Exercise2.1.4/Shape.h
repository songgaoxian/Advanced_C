#ifndef Shape_H
#define Shape_H
class Shape {
public:
	virtual void draw() = 0;
};
class Point : public Shape {
public:
	Point() {}
	virtual void draw() override {}
};

//for part d)
class Shape1 {
public:
	virtual void draw() = 0;
};
class Point1 : public Shape1 {
public:
	Point1() {}
	Point1(const Point1& src) = delete;
	Point1& operator=(const Point1& src) = delete;
	virtual void draw() override {}
};

//for part e)
class Shape2 {
public:
	virtual void draw() = 0;
};
class Point2 : public Shape2 {
public:
	Point2() {}
	Point2(const Point2&& src) {}
	Point2& operator=(const Point2&& src) {}
	virtual void draw() override {}
};
#endif

