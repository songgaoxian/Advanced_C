//Exercise4.4.5
//
//examine bucket interface
//written on 2016/6/20

#include<iostream>
#include<string>
#include<unordered_set>
#include<functional>

unsigned min_given_bucket_size = 66;

template<typename Key, typename Hash, typename EqPred>
void BucketInformation(std::unordered_set<Key, Hash, EqPred>& c) {
	//a)Show number of buckets
	std::cout << "Number of buckets:" << c.bucket_count() << '\n';
	//Show max number of buckets
	std::cout << "Max number of buckets:" << c.max_bucket_count() << '\n';
	
	//b)show current load factor
	std::cout << "Current load factor:" << c.load_factor() << '\n';
	//show max load factor
	std::cout << "Max load factor:" << c.max_load_factor() << '\n';
	
	//c)show size of each bucket
	std::cout << "Size of each bucket:\n";
	for (unsigned i = 0; i < c.bucket_count(); ++i) {
		std::cout << "Bucket " << i << " has size " << c.bucket_size(i) << '\n';
	}
	
	//d)rehash the container 
	c.rehash(min_given_bucket_size);
	std::cout << "After rehash, bucket_count=" << c.bucket_count() << '\n';
}
//define the Hash
template<typename Key>
struct myHash :std::unary_function<Key, std::size_t> {
	std::size_t operator()(const Key& key) const {
		int intKey = (int)key;
		std::size_t val = abs(intKey);
		return val % 7;
	}
};
//define EqPred
template<typename Key>
struct Equal : std::binary_function<Key, Key, bool> {
	bool operator()(const Key&key1, const Key&key2) const {
		return key1 == key2;
	}
};


int main() {
	//create an unordered set
	std::unordered_set<int, myHash<int>, Equal<int>> c;
	int N = 10;
	for (int i = 0; i < N; ++i) {
		unsigned num = rand() % 89;
		c.insert(num);
	}
	BucketInformation<int, myHash<int>, Equal<int>>(c);

	return 0;

}