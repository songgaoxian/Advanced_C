#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
//b)
//get intersection of two vector<bool>
std::vector<bool> getIntersection(const std::vector<bool>& vb1, const std::vector<bool>& vb2) {
	std::vector<bool> result;
	if (vb1.size() != vb2.size()) {
		//if sizes not same, return empty vector
		std::cout << "give same size vector<bool>\n";
		return result;
	}
	else {
		for (std::size_t i = 0; i < vb1.size(); ++i) {
			//check each element to find intersected values
			if (vb1[i] == vb2[i]) {
				result.push_back(vb1[i]);
			}
		}
	}
	return result;
}
//end of b)

int main() {
	//a) functionality supported by vector<bool>
	std::vector<bool> vb{ 1,0,0,1 };
	//support flip
	vb.flip();
	//support [] to access
	vb[2] = 0;
	std::vector<bool> vb2{ 0,0,0,0 };
	//support comparison operators
	if (vb == vb2) {
		std::cout << "vb=vb2\n";
	}
	if (vb != vb2) {
		std::cout << "vb!=vb2\n";
	}
	//can be used with hash
	std::hash<std::vector<bool>> h;
	std::cout<<h(vb)<<std::endl;
	//support resize()
	const std::size_t N = 5;
	vb.resize(N,true);
	//support clear()
	vb.clear();
	//support push_back
	vb.push_back(false);
	//support pop_back
	vb.pop_back();
	//end of a)

	std::vector<bool> vb3{ 1,0,1,0 };

	//display intersection
	std::vector<bool> r = getIntersection(vb3, vb2);
	std::cout << "\nvb3:";
	for (auto i : vb3)
		std::cout << i;
	std::cout << "\nb2:";
	for (auto i : vb2)
		std::cout << i;
	std::cout << "\nvb3 and vb2 intersect values:\n";
	for (auto i : r) {
		std::cout << i;
	}
	std::cout << '\n';
	return 0;
}