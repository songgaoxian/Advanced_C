#ifndef A_H
#define A_H
class A {
public:
	A() {}
	A(A& src) {}
	A(volatile A& src) {}
	~A() {}
};
#endif

