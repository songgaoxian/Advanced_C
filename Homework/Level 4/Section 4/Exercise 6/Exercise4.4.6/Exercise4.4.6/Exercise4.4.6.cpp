//Exercise4.4.6
//
//apply unordered set with user-defined class, user-defined hash and user-defined predicate
//written on 2016/6/21

#include<iostream>
#include<unordered_set>
#include<string>
#include<functional>
#include<sstream>
//copied
struct S {
	std::string f; std::string s;
	S(const std::string& s1, const std::string& s2) : f(s1), s(s2) {}
};

//implement hash_value function
std::size_t hash_value(const std::string& s1, const std::string& s2) {
	std::stringstream ss;
	//this stringstream stores the merge of s1 and s2
	ss << s1 << s2;
	//convert stringstream to string
	std::string resultstring = ss.str();
	std::hash<std::string> hash;
	//return hash value of string
	return hash(resultstring);
}

class SHash //Hash for class S
{
public:
	std::size_t operator()(const S& s) const {	
		return hash_value(s.f, s.s);
	}
};
class SEqual//Equality for S
{
public:
	bool operator()(const S& lhs, const S& rhs) const {
		return (rhs.f == lhs.f && rhs.s == lhs.s);
	}
};

int main() {
	std::unordered_set<S, SHash, SEqual> mySet;
	//a)add elements to mySet
	mySet.insert(S("abc", "efg"));
	mySet.insert(S("efg", "abc"));
	mySet.emplace(S("Hello", "World"));
	mySet.emplace(S("WOrld", "HEllo"));
	mySet.emplace(S("never giveUP", "As He will Come"));
	mySet.insert(S("Do not Base Truth on a book", "book--Unreliable"));
	mySet.insert(S("123678", "909011"));
	mySet.insert(S("Holy!=He", "He>Holy"));
	mySet.insert(S("Last Day", "Relieve"));

	//b)Examine bucket info
	std::cout << "Number of buckets:" << mySet.bucket_count() << '\n';
	std::cout << "Max number of buckets:" << mySet.max_bucket_count() << '\n';
	std::cout << "Current load factor:" << mySet.load_factor() << '\n';
	std::cout << "Max load factor:" << mySet.max_load_factor() << '\n';
	//show each bucket size
	for (unsigned i = 0; i < mySet.bucket_count(); ++i) {
		std::cout<<"Bucket "<<i <<":"<< mySet.bucket_size(i) << '\n';
	}
	mySet.rehash(mySet.bucket_count() * 2);
	//show bucket size
	std::cout << "After rehash: number of buckets=" << mySet.bucket_count() << '\n';


	return 0;
}