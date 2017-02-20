#include<iostream>
#include<ratio>

int main() {
	//a)create instances
	using one_two = std::ratio<1, 2>;
	using two_four = std::ratio<2, 4>;
	//print out
	std::cout << "one_two: " << one_two::num << "/" << one_two::den << std::endl;
	std::cout << "two_four: " << two_four::num << "/" << two_four::den << std::endl;

	//b)
	using one_three = std::ratio<1, 3>;
	using eight_seven = std::ratio<8, 7>;
	//add
	using sum = std::ratio_add<one_three, eight_seven>;
	//multiply
	using product = std::ratio_multiply<one_three, eight_seven>;
	//divide
	using divide = std::ratio_divide<eight_seven, one_three>;
	//subtract
	using subtract = std::ratio_subtract<one_three, eight_seven>;
	//print out
	std::cout << "add: " << sum::num << "/" << sum::den << std::endl;
	std::cout << "multiply: " << product::num << "/" << product::den << std::endl;
	std::cout << "divide: " << divide::num << "/" << divide::den << std::endl;
	std::cout << "subtract: " << subtract::num << "/" << subtract::den << std::endl;

	return 0;

}