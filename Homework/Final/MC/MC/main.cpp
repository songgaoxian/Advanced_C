//test the codes

#include "Mediator.hpp"
#include<boost\thread\thread.hpp>
#include<mutex>
#include<array>

std::mutex mtx;

void ShowSummary(Pricer& p) {
	std::lock_guard<std::mutex> lck(mtx);
	p.Summary();
}

void Connection1(MCMediator& mc, std::shared_ptr<EuropeanPricer>& ptr) {
	mc.path.connect(boost::bind(&EuropeanPricer::ProcessPath, &*ptr, boost::placeholders::_1));
	mc.finish.connect(boost::bind(&EuropeanPricer::PostProcess, &*ptr, 1));
}
void Connection2(MCMediator& mc, std::shared_ptr<BarrierPricer>& ptr) {
	mc.path.connect(boost::bind(&BarrierPricer::ProcessPath, &*ptr, boost::placeholders::_1));
	mc.finish.connect(boost::bind(&BarrierPricer::PostProcess, &*ptr, 2));
}
void Connection3(MCMediator& mc, std::shared_ptr<AssianPricer>& ptr) {
	mc.path.connect(boost::bind(&AssianPricer::ProcessPath, &*ptr, boost::placeholders::_1));
	mc.finish.connect(boost::bind(&AssianPricer::PostProcess, &*ptr, 3));
}

int main() {
	BuilderFactory bf;
	//variables to store start and end time
	std::chrono::system_clock::time_point stop, start = std::chrono::system_clock::now();

	//declare initial values
	double R = 0.08, V = 0.3, Div = 0.0, IC = 60.0, T = 0.25, K = 55.0, beta = 0.5;
	char type = 'c';
	std::tuple<double, double, double, double, double, double, char> srcdata(R, V, Div, IC, T, K, type);//parameter to construct optiondata
	//create 3 option data
	OptionData opt1(srcdata);
	std::get<3>(srcdata) = K;
	OptionData opt2(srcdata);
	std::get<6>(srcdata) = 'p';
	OptionData opt3(srcdata);
	//create 2 default builder
	DefaultBuilder db1(opt2);
	DefaultBuilder db2(opt3);
	//create 3 parts, you can customize first one
	T_Composite parts1 = bf.ImplementBuilder(opt1,beta), parts2 = db1.Parts(), parts3 = db2.Parts();
	
	//specify num of simulations	
	//long long N = 30'000'000;//tested, takes a very long time, but gives valid results
	long long N = 30'000;
	double bar=50;//store barrier of barrier option
	bool sta = true;//store initial status of barrier option
	MCMediator mcm1(parts1,N,1), mcm2(parts2,N,2), mcm3(parts3,N,3);//declare three mediators
	//const int size_v = 3; //store size of vector size
	
	//declare shared pointers for pricers
	std::shared_ptr<EuropeanPricer> ep1(new EuropeanPricer(opt1)), ep2(new EuropeanPricer(opt2)), ep3(new EuropeanPricer(opt3));
	std::shared_ptr<BarrierPricer> bp1(new BarrierPricer(opt1,bar,sta)), bp2(new BarrierPricer(opt2,bar,!sta)), bp3(new BarrierPricer(opt3,bar,sta));
	std::shared_ptr<AssianPricer> ap1(new AssianPricer(opt1)), ap2(new AssianPricer(opt2)), ap3(new AssianPricer(opt3));

    //connect signals
	Connection1(mcm1, ep1); Connection1(mcm2, ep2); Connection1(mcm3, ep3);
	Connection2(mcm1, bp1); Connection2(mcm2, bp2); Connection2(mcm3, bp3);
	Connection3(mcm1, ap1); Connection3(mcm2, ap2); Connection3(mcm3, ap3);
	
	//create thread_groups to run several threads
	boost::thread_group threads, threads2;

	//use thread group to run start()
	threads.create_thread(boost::bind(&MCMediator::start, &mcm1));
	threads.create_thread(boost::bind(&MCMediator::start, &mcm2));
	threads.create_thread(boost::bind(&MCMediator::start, &mcm3));
	//join all threads
     threads.join_all();

	 //store processed pricer pointers in arrays
	 std::shared_ptr<EuropeanPricer> ep[3] = { ep1,ep2,ep3 };
	 std::shared_ptr<BarrierPricer> bp[3] = { bp1,bp2,bp3 };
	 std::shared_ptr<AssianPricer> ap[3] = { ap1,ap2,ap3 };
	//show the summary by using thread group
	for (int i = 0; i < 3; ++i) {
		threads2.create_thread(boost::bind(&ShowSummary, *ep[i]));
		threads2.create_thread(boost::bind(&ShowSummary, *bp[i]));
		threads2.create_thread(boost::bind(&ShowSummary, *ap[i]));
	}
	//join all threads
	threads2.join_all();
	
	//record finish time
	stop = std::chrono::system_clock::now();

	//get duration
	std::chrono::duration<double> d = stop - start;
	std::cout << "\n------The total process takes " << d.count() << " seconds------\n";

	return 0;

}