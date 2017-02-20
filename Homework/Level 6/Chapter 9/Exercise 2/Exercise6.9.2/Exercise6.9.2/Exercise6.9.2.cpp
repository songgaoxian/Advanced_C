//Exercise6.9.2.cpp
//test codes of versions of SUD and related classes

#include"SUD.hpp"
#include<complex>
#include"SUD_b.hpp"
#include"Origin.hpp"

using C_Double = std::complex<double>;

//functions: convert double to C_Double
C_Double free_convert(const double& t) { return (C_Double)t; }//free function
//lambda function
auto lambda_convert = [](const double& t)->C_Double {return (C_Double)t; };
//static member function, member function and function object
class Multi_Convert {
public:
	static C_Double static_convert(const double& t) { return (C_Double)t; }
	C_Double operator()(const double& t) { return (C_Double)t; }
	C_Double convert(const double& t) { return (C_Double)t; }
};

int main() {
	//test with scalar type
	SUD<double, int, MySource, MySink, MyProcess> sud_scalar;
	sud_scalar.run();
	//test with composite type
	SUD<int, C_Double, MySource, MySink, MyProcess> sud_composite;
	sud_composite.run();

	//SUD_b is more flexible as we can customize converter without rewriting a class
	using SUD_bType = SUD_b<double, C_Double, MySource_b, MySink_b>;
	//free function
	SUD_bType sud_b1(free_convert);
	std::cout << "\nFree function as converter:\n";
	sud_b1.run();
	//lambda function
	SUD_bType sud_b2(lambda_convert);
	std::cout << "\nLambda function as converter:\n";
	sud_b2.run();
	//static member function
	Multi_Convert mc;
	SUD_bType sud_b3(Multi_Convert::static_convert);
	std::cout << "\nStatic function as converter:\n";
	sud_b3.run();
	//function object
	SUD_bType sud_b4(mc);
	std::cout << "\nFunction object as converter:\n";
	sud_b4.run();
	//binded member function
	SUD_bType sud_b5(std::bind(&Multi_Convert::convert, &mc,std::placeholders::_1));
	std::cout << "\nBinded member function as converter:\n";
	sud_b5.run();

	//test codes of c)
	SUD_O<MyInput, MyOutput, MyConverter>  sud_o;
	std::cout << "\nProcess files\n";
	sud_o.run();

	return 0;
}