//Observer.h
//
//Create Observer, LongFormat and DoubleFormat classes
//written on 2016/7/2

#ifndef Observer_H
#define Observer_H

#include"Subject.hpp"

//i)create Observer
class Observer {
public:
	//j)create Update()
	virtual void Update(Subject& sub) = 0;
};
//k)create two observer classes
class LongFormat :public Observer
{
public:
	void Update(Subject& sub);
};
class DoubleFormat : public Observer
{
public:
	void Update(Subject& sub);
};



#endif
