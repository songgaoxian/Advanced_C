#include "TMPClass.h"

int main() {
	InputFunction f1 = []() {return 2.0; };
	OutputFunction f2 = [](const std::vector<double>& vc) {
		for (auto i : vc) {
			std::cout << i <<" ";
		}
		std::cout << "end\n";
	};
	TMPClass tpm(10,1.0,f1,f2);
	tpm.Calculate();
	return 0;
}