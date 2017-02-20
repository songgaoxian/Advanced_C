#include "C.h"
int main() {
	Shape sp1;
	Shape sp2(sp1);
	Shape sp3("c");
	double d = 10.2;
	std::cout << "Rotate sp1: \n";
	sp1.rotate(d);
	std::cout << "Rotate sp2: \n";
	sp2.rotate(d);
	std::cout << "Rotate sp3: \n";
	sp3.rotate(d);
	return 0;

}