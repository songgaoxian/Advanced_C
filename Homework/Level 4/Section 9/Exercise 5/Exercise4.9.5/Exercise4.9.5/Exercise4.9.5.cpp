//Exercise4.9.5
//
//reengineer GOF observer pattern
//written on 2016/6/23
#include"Subject.h"

int main() {
	//c)connect slots to a signal
	//create the notifier
	Subject mySubject;

	//create attentionSig slots
	Print myPrint;
	MathsWhiz myMaths(10.0);
	Database myDatabase;

	//connect
	mySubject.AddObserver(myPrint);
	mySubject.AddObserver(myMaths);
	mySubject.AddObserver(myDatabase);
	mySubject.AddObserver(&CPrint);

	//trigger event
	std::cout << "Give the value: "; double val; std::cin >> val;

	mySubject.ChangeEvent(val);

	return 0;
}