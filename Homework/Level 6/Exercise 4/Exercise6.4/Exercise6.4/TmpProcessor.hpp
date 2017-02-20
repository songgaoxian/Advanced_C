//TmpProcessor.hpp
//
//declare class TmpProcessor
//written on 2016/7/14

#ifndef TmpProcessor_HPP
#define TmpProcessor_HPP

#include<functional>
//function categories
template<typename T>
using FactoryFunction = std::function<T()>;

template<typename T>
using ComputeFunction = std::function<T(const T& t)>;

template<typename T>
using DispatchFunction = std::function<void(T& t)>;
//copied  
template<typename T>
class TmpProcessor
{
private:
	FactoryFunction<T> _factory;
	ComputeFunction<T> _compute;
	DispatchFunction<T> _dispatch;
	
public:
	TmpProcessor(const FactoryFunction<T>& factory,
		const ComputeFunction<T>& compute,
		const DispatchFunction<T>& dispatch)
		:_factory(factory), _compute(compute), _dispatch(dispatch) {}

	//template method pattern
	virtual void algorithm() final
	{
		T val = _factory();
		T val2 = _compute(val);
		_dispatch(val2);
	}
};




#endif
