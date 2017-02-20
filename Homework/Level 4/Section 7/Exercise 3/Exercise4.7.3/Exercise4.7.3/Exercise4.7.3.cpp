//Exercise4.7.3
//
//implement association of UML book entity with bimap
//written on 2016/6/21

#include<iostream>
#include<boost/bimap.hpp>
#include<boost/bimap/set_of.hpp>
#include<boost/bimap/multiset_of.hpp>
#include<boost/config.hpp>
#include<tuple>
#include<string>
struct Author{};
struct Title{};


//a)
//assume one book can be written by multiple authors
using bookBimap = boost::bimap<boost::bimaps::set_of<boost::bimaps::tagged<std::string,Author>>, //Author
	boost::bimaps::multiset_of<boost::bimaps::tagged<std::string,Title>>, //Title
	boost::bimaps::with_info<double>>;

using book = bookBimap::value_type;

//c)
//create association attribute containing a tuple
using bookBimap2 = boost::bimap<boost::bimaps::set_of<boost::bimaps::tagged<std::string, Author>>, //Author
	boost::bimaps::multiset_of<boost::bimaps::tagged<std::string, Title>>, //Title
	boost::bimaps::with_info<std::tuple<std::string,double>>>;

using book2 = bookBimap2::value_type;


int main() {
	//a)create bimap which has 1:N association between title and author
	bookBimap bimap;
	//insert book to bimap
	bimap.insert(book("John", "C++", 33.4));
	bimap.insert(book("Tim", "C++", 33.4));
	bimap.insert(book("Ben", "Find Truth", 55.5));
	bimap.insert(book("Lucy", "Work Hard", 12.3));

	//b)
	//given author
	std::string author = "Tim";
	//find the book written by author
	auto i = bimap.by<Author>().find(author);
	//print price
	std::cout <<"Book written by "<<author<<" is priced at "<<i->info<<'\n';

	//c)
	//create an instance of bookBimap2
	bookBimap2 bimap2;
	//insert into bimap2
	bimap2.insert(book2("John", "C++", std::make_tuple("abstract of c++", 33.4)));
	bimap2.insert(book2("Tim", "C++", std::make_tuple("abstract of c++", 33.4)));
	bimap2.insert(book2("Lucy", "Work Hard", std::make_tuple("abstract", 12.3)));
	//print info
	std::tuple<std::string, double> stuple = bimap2.by<Author>().find(author)->info;
	std::cout << "Book written by " << author << " has abstract " << std::get<0>(stuple) << " and priced at " << std::get<1>(stuple) << '\n';

	return 0;

}



