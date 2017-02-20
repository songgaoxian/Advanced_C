#ifndef Proposition_H
#define Proposition_H
#include<bitset>

class Proposition {
 //a class representing true/false
private:
	std::bitset<1> data;
public:
	//a)default constructor
	Proposition() { data[0] = 0; }
	//bool as argument
	Proposition(bool src) { data[0] = (int)src; }
	//std::bitset<1> as argument
	Proposition(std::bitset<1> src): data(src) {}
	//destructor
	~Proposition() {}
	//give data info
	bool Getdata() const { return data[0]; }

	//b)
	//equality
	Proposition operator==(const Proposition& src) const {
		return Proposition(data[0] == src.data[0]);
	}
	//inequality
	Proposition operator!=(const Proposition& src) const {
		return Proposition(data[0] != src.data[0]);
	}
	//and
	Proposition operator&(const Proposition& src) const {
		return Proposition(data[0] & src.data[0]);
	}
	//or
	Proposition operator|(const Proposition& src) const {
		return Proposition(data[0] | src.data[0]);
	}
	//XOR
	Proposition operator^(const Proposition& src) const {
		return Proposition(data[0] ^ src.data[0]);
	}
	//negation
	Proposition operator!() const {
		return Proposition(!data[0]);
	}
	//assignment
	Proposition assign(bool src) const {
		return Proposition(src = data[0]);
	}
	//conditional
	friend Proposition operator%(const Proposition& A,const Proposition& B) {
		//get the bool result of A->B
		if (A.data[0] == 1 && B.data[0] == 0)
			return Proposition(false);
		else
			return Proposition(true);
	}
	//biconditional
	friend Proposition bicondition(const Proposition& A,const Proposition& B) {
		return (A%B)&(B%A);
	}
};


#endif
