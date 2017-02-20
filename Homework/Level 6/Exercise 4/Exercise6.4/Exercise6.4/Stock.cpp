//Stock.cpp
//implement class Stock
//written on 2016/7/14

#include"Stock.hpp"
#include<random>

std::default_random_engine generator;
std::normal_distribution<double> dist(0, 1);

Stock::Stock() :s(48), mu(1.0 / 24.0), sigma(0.25), dt(0.01), t(0.0),k(48.0),expire(1.0) {
	z = dist(generator);
}
Stock::Stock(const Stock& stk) : s(stk.s), mu(stk.mu), sigma(stk.sigma), dt(stk.dt), t(stk.t), z(stk.z),k(stk.k),expire(stk.expire) {}

double Stock::S() const { return s; }
double Stock::T() const { return t; }
double Stock::MU() const { return mu; }
double Stock::Sig() const { return sigma; }
double Stock::K() const { return k; }
double Stock::Expire() const { return expire; }

//advance 1 step
void Stock::advance() {
	//update member data
	s += s*mu*dt + sigma*s*std::sqrt(dt)*z;
	t += dt;
	mu = (50.0 - s) / s*(expire - t);
	sigma = std::sqrt(expire - t) / 4.0;
	z = dist(generator);
}