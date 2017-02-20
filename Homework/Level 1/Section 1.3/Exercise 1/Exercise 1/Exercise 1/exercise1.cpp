#include<bitset>
#include<iostream>

template<typename T, typename... Types>
void print(const T& input1, const Types&... args) {
	std::cout << input1 << std::endl;
	print(args...);
}

template<typename T>
void print(const T& input) {
	std::cout << input << std::endl;
}

int main() {
	int j = 1; double d = 2.0;
	print(j); print(d); print(j, d); print(d, j);
	std::cout << "\n3 params \n";
	print(d, j, std::bitset<8>(233));
	return 0;
}