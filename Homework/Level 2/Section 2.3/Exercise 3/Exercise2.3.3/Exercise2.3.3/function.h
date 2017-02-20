#ifndef Function_H
#define Function_H
#include<cmath>
#include<algorithm>
//function maps domain to range
template<typename R, typename D>
using FunctionType = std::function<R(const D x)>;

//working function type
using ScalarFunction = FunctionType<double, double>;

//for a)
//create function to do add
template<typename R, typename D>
FunctionType<R, D> operator+(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return addition of functions
	return[=](const D& x) {
		return f(x) + g(x);
	};
}
//create function to multiply two functions
template<typename R, typename D>
FunctionType<R, D> operator*(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return multiplication of functions
	return [=](const D& x) {
		return f(x)*g(x);
	};
}
//create function to substract two functions
template<typename R, typename D>
FunctionType<R, D> operator-(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return the substraction result of functions
	return [=](const D& x) {
		return f(x) - g(x);
	};
}
//create unary additive inverse function
template<typename R, typename D>
FunctionType<R, D> operator-(const FunctionType<R, D>& f) {
	//return the unary inverse of the function
	return [=](const D& x) {
		return -f(x);
	};
}
//create scalar multiplication function with scalar coming first
template<typename R, typename D, typename Scalar>
FunctionType<R, D> operator*(const Scalar& scalar, const FunctionType<R, D>& f) {
	//return the scalar multiplication result
	return [=](const D& x) {
		return (R)scalar*f(x);
	};
}
//create scalar multiplication function with function coming first
template<typename R, typename D, typename Scalar>
FunctionType<R, D> operator*(const FunctionType<R, D>& f, const Scalar& scalar) {
	//return the scalar multiplication result
	return [=](const D& x) {
		return f(x)*(R)scalar;
	};
}
//create division of functions
template<typename R, typename D>
FunctionType<R, D> operator/(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return the division result
	return [=](const D& x) {
		return f(x) / g(x);
	};
}
//create composition of functions
template<typename R, typename D>
FunctionType<R, D> operator<<(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return the composition of functions
	return [=](const D& x) {
		return f(g(x));
	};
}
//end of part a)

//for b)
//implement cos
template<typename R, typename D>
FunctionType<R, D> cos(const FunctionType<R, D>& f) {
	//return the cos function
	return [=](const D& x) {
		return std::cos(f(x));
	};
}
//implement sin
template<typename R, typename D>
FunctionType<R, D> sin(const FunctionType<R, D>& f) {
	//return the sin function
	return [=](const D& x) {
		return std::sin(f(x));
	};
}
//implement tan
template<typename R, typename D>
FunctionType<R, D> tan(const FunctionType<R, D>& f) {
	//return the tan function
	return [=](const D& x) {
		return std::tan(f(x));
	};
}
//implement exp
template<typename R, typename D>
FunctionType<R, D> exp(const FunctionType<R, D>& f) {
	//return the exp function
	return [=](const D& x) {
		return std::exp(f(x));
	};
}
//implement log
template<typename R, typename D>
FunctionType<R, D> log(const FunctionType<R, D>& f) {
	//return the log function
	return [=](const D& x) {
		return std::log(f(x));
	};
}
//implement abs
template<typename R, typename D>
FunctionType<R, D> abs(const FunctionType<R, D>& f) {
	//return the abs function
	return [=](const D& x) {
		return std::abs(f(x));
	};
}
//implement sqrt
template<typename R, typename D>
FunctionType<R, D> sqrt(const FunctionType<R, D>& f) {
	//return the sqrt function
	return [=](const D& x) {
		return std::sqrt(f(x));
	};
}
//end of b)

//for c)
//implement max
template<typename R, typename D>
FunctionType<R, D> max(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return the max function
	return [=](const D& x) {
		return std::max(f(x), g(x));
	};
}
//implement min
template<typename R, typename D>
FunctionType<R, D> min(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	//return the min function
	return [=](const D& x) {
		return std::min(f(x), g(x));
	};
}
//end of c)

#endif

