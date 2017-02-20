//Exercise4.1.1
//
//exercise to use trim, start_with, etc string algo
//written on 2016/6/17

#include<boost/algorithm/string.hpp>
#include<iostream>
#include<string>
#include<algorithm>

int main() {
	//create some strings
	std::string s1("       abc123    ");
	std::string s2("       A12B34D33 */  ");
	std::cout << "original strings:\n";
	std::cout << "s1:" << s1 << "\ns2:" << s2 << '\n';

	//a)
	std::cout << "\na)\n";
	//trim s1 for leading blanks
	boost::algorithm::trim(s1);
	//trim s1 for trailing blanks
	boost::algorithm::trim_right(s1);
	//display s1 after triming
	std::cout << "after trim, s1:" << s1 << '\n';

	//copy of input string
	std::string scopy = boost::algorithm::trim_copy(s2);
	scopy = boost::algorithm::trim_right_copy(scopy);
	std::cout << "after trim_copy, s2:" << s2 << '\n';
	std::cout << "scopy:" << scopy << '\n';

	//b)
	std::cout << "\nb)\n";
	//create two strings
	std::string s3("AAA234eeefffJJJ");
	std::string s4("BBBefg888DDD");
    //use different predicates
	boost::algorithm::trim_left_if(s3, boost::algorithm::is_any_of("AJ")||boost::algorithm::is_digit());
	boost::algorithm::trim_right_if(s3, boost::algorithm::is_any_of("AJ") || boost::algorithm::is_digit());
	std::cout <<"after trime, s3:"<<s3<<'\n';
	
	//use different predicates
	scopy = boost::algorithm::trim_left_copy_if(s4, boost::algorithm::is_alpha() && boost::algorithm::is_upper());
	scopy = boost::algorithm::trim_right_copy_if(scopy, boost::algorithm::is_alpha() && boost::algorithm::is_upper());
	std::cout << "after trim_copy, s4:" << s4 << '\n';
	std::cout << "scopy:" << scopy << '\n';

	//c)test if a string starts or ends with a given string
	std::string givenString = "abC";
	//strings to test
	std::string s5("abCmmmqqqabC");
	std::string s6("ABCmmmqqqabc");
	std::boolalpha(std::cout);
	//test case sensitive
	std::cout << "\nc)\n" << "Case sensitive test:\n";
	//test s5
	std::cout << "s5 starts with abC? " << boost::algorithm::starts_with(s5, givenString) << '\n';
	std::cout << "s5 ends with abC? " << boost::algorithm::ends_with(s5, givenString) << '\n';
	//test s6
	std::cout << "s6 starts with abC? " << boost::algorithm::starts_with(s6, givenString) << '\n';
	std::cout << "s6 ends with abC? " << boost::algorithm::ends_with(s6, givenString) << '\n';

	//test case insensitive
	std::cout << "\nCase insensitive test:\n";
	//test s6
	std::cout << "s6 starts with abC? " << boost::algorithm::istarts_with(s6, givenString) << '\n';
	std::cout << "s6 ends with abC? " << boost::algorithm::iends_with(s6, givenString) << '\n';

	//d)test if a string contains another string
	std::cout << "\nd)\n";
	//case sensitive test
	std::cout << "Case sensitive test:\n";
	std::cout << "Does s5 contain givenString? " << boost::algorithm::contains(s5, givenString) << '\n';
	std::cout << "Does s6 contain givenString? " << boost::algorithm::contains(s6, givenString) << '\n';

	//case insensitive test
	std::cout << "\nCase insensitive test:\n";
	std::cout << "Does s6 contain givenString? " << boost::algorithm::icontains(s6, givenString) << '\n';

	//strings to test if equal with givenString
	std::string s7("abC");
	std::string s8("abc");
	std::cout << "\nCase sensitive test:\n";
	//case sensitive test
	std::cout << "Does s7 equal to givenString? " << boost::algorithm::equals(s7, givenString) << '\n';
	std::cout << "Does s8 equal to givenString? " << boost::algorithm::equals(s8, givenString) << '\n';

	std::cout << "\nCase insensitive test:\n";
	//case insensitive test
	std::cout << "Does s8 equal to givenString? " << boost::algorithm::iequals(s8, givenString) << '\n';


	return 0;

}