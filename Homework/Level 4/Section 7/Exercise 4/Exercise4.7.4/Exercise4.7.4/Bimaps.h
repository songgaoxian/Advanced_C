//Bimaps.h
//
//define different types of bimaps with different containers type
//written on 2016/6/22

#ifndef Bimaps_H
#define Bimaps_H
#include<boost/bimap.hpp>
#include<boost/bimap/set_of.hpp>
#include<boost/bimap/multiset_of.hpp>
#include<boost/bimap/unordered_set_of.hpp>
#include<boost/bimap/list_of.hpp>
#include<string>
#include"Comparator.h"
//a) create bimaps with required domain and range
//using Bset_list = boost::bimap<boost::bimaps::set_of<std::string>,
	//boost::bimaps::list_of<int>>;
//c)use other comparitor
using Bset_list = boost::bimap<boost::bimaps::set_of<std::string, std::greater<std::string>>,
	boost::bimaps::list_of<int>>;
using set_list = Bset_list::value_type;

//using Bset_set = boost::bimap<boost::bimaps::set_of<std::string>,
	//boost::bimaps::set_of<int>>;
//c)use other comparitor
using Bset_set = boost::bimap<boost::bimaps::set_of<std::string,Greater<std::string>>,
	boost::bimaps::set_of<int,Greater<int>>>;
using set_set = Bset_set::value_type;

//using Bset_unordered = boost::bimap<boost::bimaps::set_of<std::string>,
	//boost::bimaps::unordered_set_of<int>>;
//c)use other comparitor
using Bset_unordered = boost::bimap<boost::bimaps::set_of<std::string>,
	boost::bimaps::unordered_set_of<int,std::hash<int>,Equal<int>>>;
using set_unordered = Bset_unordered::value_type;

using Bmulset_list = boost::bimap<boost::bimaps::multiset_of<std::string>,
	boost::bimaps::list_of<int>>;
using mulset_list = Bmulset_list::value_type;

using Bmulset_set = boost::bimap<boost::bimaps::multiset_of<std::string>,
    boost::bimaps::set_of<int>>;
using mulset_set = Bmulset_set::value_type;

using Bmulset_unordered = boost::bimap<boost::bimaps::multiset_of<std::string>,
	boost::bimaps::unordered_set_of<int>>;
using mulset_unordered = Bmulset_unordered::value_type;

using Bunordered_list = boost::bimap<boost::bimaps::unordered_set_of<std::string>,
	boost::bimaps::list_of<int>>;
using unordered_list = Bunordered_list::value_type;

//using Bunordered_set= boost::bimap<boost::bimaps::unordered_set_of<std::string>,
	//boost::bimaps::set_of<int>>;
//c)use comparitor
using Bunordered_set = boost::bimap<boost::bimaps::unordered_set_of<std::string>,
	boost::bimaps::set_of<int,Less<int>>>;
using unordered_set = Bunordered_set::value_type;

using Bunordered_unordered= boost::bimap<boost::bimaps::unordered_set_of<std::string>,
	boost::bimaps::unordered_set_of<int>>;
using unordered_unordered = Bunordered_unordered::value_type;


#endif
