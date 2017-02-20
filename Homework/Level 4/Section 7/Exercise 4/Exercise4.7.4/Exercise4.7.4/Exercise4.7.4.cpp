//Exercise4.7.4
//
//apply bimaps implemented by different containers
//written on 2016/6/22

#include"Bimaps.h"
#include<iostream>

template<typename Bmap>
void print(const Bmap& bm,std::string name) {
	std::cout << "Print out contents of " << name << '\n';
	//iterator bm
	for (auto it = bm.begin(); it != bm.end(); it++) {
		//print out left and right elements
		std::cout << "(" << it->left << "," << it->right << ") ";
	}
	std::cout << "\n\n";
}

template<typename Bmap, typename value>
void insert(Bmap& b_map) {
	//insert data to bmap
	b_map.insert(value("abc", 5));
	b_map.insert(value("efg", 5));
	b_map.insert(value("ABC", 7));
	b_map.insert(value("abc", 7));
}

int main() {
	//b)
	//create Bset_list
	Bset_list slst;
	//insert values to slst
	insert<Bset_list, set_list>(slst);
	//print values of slst
	//c)
	std::cout << "The comparitor used in Set is std::greater\n";
	print<Bset_list>(slst, "Bimap<Set, List>");

	//create Bset_set
	Bset_set sset;
	insert<Bset_set, set_set>(sset);
	//c)
	std::cout << "The comparitors used for sets are self-defined Greater\n";
	print<Bset_set>(sset, "Bimap<Set,Set>");

	//create Bset_unordered
	Bset_unordered sunorder;
	insert<Bset_unordered, set_unordered>(sunorder);
	//c)
	std::cout << "The comparitor used for unordered_set is self-defined Equal\n";
	print<Bset_unordered>(sunorder, "Bimap<Set,Unordered>");

	//create Bmulset_list
	Bmulset_list mlst;
	insert<Bmulset_list, mulset_list>(mlst);
	print<Bmulset_list>(mlst,"Bimap<Multiset,List>");

	//create Bmulset_set
	Bmulset_set mset;
	insert<Bmulset_set, mulset_set>(mset);
	print<Bmulset_set>(mset, "Bimap<Multiset,Set>");

	//create Bmulset_unordered
	Bmulset_unordered munorder;
	insert<Bmulset_unordered, set_unordered>(munorder);
	print<Bmulset_unordered>(munorder, "Bimap<Multiset,Unordered>");

	//create Bunordered_list
	Bunordered_list ulst;
	insert<Bunordered_list, unordered_list>(ulst);
	print<Bunordered_list>(ulst, "Bimap<Unordered,List>");

	//create Bunordered_set
	Bunordered_set uset;
	insert<Bunordered_set, unordered_set>(uset);
	//c)
	std::cout << "The comparitor used for set is self-defined Less\n";
	print<Bunordered_set>(uset, "Bimap<Unordered,Set>");

	//create Bunordered_unordered
	Bunordered_unordered unorder;
	insert<Bunordered_unordered, unordered_unordered>(unorder);
	print<Bunordered_unordered>(unorder, "Bimap<Unordered,Unordered>");

	return 0;
	
}