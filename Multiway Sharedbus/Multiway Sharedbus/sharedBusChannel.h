#include "interfaceClasses.h"

template <class T, int numOfInitiators, int numOfTargets>
class sharedBus : public put_if<T>, public get_if<T>
{
	int comingFrom, goingTo;
	T dataPlaced;
	sc_event dataAvailable[numOfTargets];
	sc_event dataReceived[numOfTargets];

	sc_mutex busBusy;

	public:
		sharedBus() : comingFrom(-1), goingTo(-1) {};
		~sharedBus() {};
		void put(int initiator, int target, T data){
			busBusy.lock(); 
			comingFrom = initiator;
			goingTo = target;
			dataPlaced = data;
			dataAvailable[target].notify();
			wait(dataReceived[target]);
			busBusy.unlock();
		}
		void get(int &initiator, int target, T &data){
			if (goingTo != target) wait(dataAvailable[target]);
			initiator = comingFrom;
			data = dataPlaced;
			comingFrom = -1;
			goingTo = -1; // prevent multiple gets of same data
			dataReceived[target].notify();
		}
};
