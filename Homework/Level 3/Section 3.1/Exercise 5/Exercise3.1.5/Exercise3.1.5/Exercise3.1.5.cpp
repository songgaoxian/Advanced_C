#include<atomic>
#include<iostream>


int main() {
	//create atomic objects of type long long, bool and int
	std::atomic_llong all(99);
	std::atomic_bool abl(true);
	std::atomic_int aint(10);
	

	//check if lock free
	std::cout << "lock free? \n";
	std::cout << "long long type: "<<std::boolalpha<<all.is_lock_free()<<std::endl;
	std::cout << "bool type: "<<std::boolalpha<<abl.is_lock_free()<<std::endl;
	std::cout << "int type: "<<std::boolalpha<<aint.is_lock_free()<<std::endl;

	//replace value of one atomic object by another
	all.store(abl);
	std::cout << "all=" << all << "; abl=" << abl << std::endl;

	//atomically load an atomic object and return its current value
	std::cout <<"current all: " <<all.load()<< std::endl;
	std::cout <<"current abl: "<< abl.load() << std::endl;
	std::cout <<"current aint: " <<aint.load()<< std::endl;
	return 0;

}