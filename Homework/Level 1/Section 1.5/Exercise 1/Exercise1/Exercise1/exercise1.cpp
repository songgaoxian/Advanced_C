#include <boost/date_time/gregorian/gregorian.hpp>
#include<iostream>
#include<string>
#include<tuple>
#include<vector>
using namespace std;
using namespace boost::gregorian;

struct Person {
	tuple<string, string, date> pinfo;
	Person(string name, string address, date birthday){
		pinfo = make_tuple(name, address, birthday);
		cout << "Created a person\n";
	}
	Person() {
		pinfo = make_tuple("na", "na", date(from_simple_string("1990-1-1")));
		cout << "Create a person with default input\n";
	}
	void ChangeName(string newname) {
		get<0>(pinfo) = newname;
	}
	void ChangeAddress(string newaddress) {
		get<1>(pinfo) = newaddress;
	}
	void ChangeBirthday(date newbirthday) {
		get<2>(pinfo) = newbirthday;
	}
};

void print(Person& p) {
	cout << "Info about the person: \n";
	cout << "Name: " << get<0>(p.pinfo) << endl;
	cout << "Address: " << get<1>(p.pinfo) << endl;
	cout << "Birthday: " << to_simple_string(get<2>(p.pinfo)) << endl;
}
template<int index> 
struct CompareTuple {
	bool operator()(const Person& left, const Person& right) const {
		return get<index>(left.pinfo) < get<index>(right.pinfo);
	}
};
void Sort(vector<Person>& input) {
	sort(input.begin(), input.end(), CompareTuple<0>());
}

int main() {
	Person p1;
	Person p2("John", "23rd Street", date(from_simple_string("1985-4-9")));
	Person p3("Any", "5th Street", date(from_simple_string("1991-8-3")));
	p1.ChangeName("David");
	p1.ChangeAddress("56th Avenue");
	p1.ChangeBirthday(date(from_simple_string("1990-6-7")));
	print(p1);
	print(p2);
	vector<Person> vp = { p1,p2};
	vp.push_back(p3); vp.push_back(Person("Tom", "44th Street", date(from_simple_string("1991-4-3"))));
	vp.push_back(Person("Amy", "33th Street", date(from_simple_string("2000-3-3"))));
	//sort by name
	Sort(vp);
	cout << "After sort:\n";
	for (int i = 0; i < vp.size(); i++)
		print(vp[i]);

	return 0;
}