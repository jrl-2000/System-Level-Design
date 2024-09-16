#include "interfaceClasses.h"

// data type, number of Inititiators, number of Targets
template <class T, int nI, int nT> 
class prioritySBus : public put_if<T>, public get_if<T>
{
	int comingFrom, goingTo;
	T dataPlaced;
	sc_event dataAvailable[nT];
	sc_event dataReceived[nT];
	sc_event busReleased;

	bool requestingI[nI]; // requesting Initiators
	bool busBusy;

	int priority(int, bool*);

	public:
		prioritySBus() : comingFrom(-1), goingTo(-1), busBusy(false) {};
		~prioritySBus() {};

		void put(int initiator, int target, T data, int delay){
			wait(delay, SC_NS);
			requestingI[initiator] = true;
			while (busBusy || (initiator != priority(nI, requestingI))) {
				wait(busReleased);
			}
			requestingI[initiator] = false;
			busBusy = true;
			comingFrom = initiator; 
			goingTo = target;
			dataPlaced = data;
			dataAvailable[target].notify();
			wait(dataReceived[target]);
			busBusy = false;
			busReleased.notify();
		}
		void get(int &initiator, int target, T &data, int delay){
			if (goingTo != target) wait(dataAvailable[target]);
			initiator = comingFrom;
			data = dataPlaced;
			wait(delay, SC_NS);
			comingFrom = -1;
			goingTo = -1; // prevent multiple gets of same data
			dataReceived[target].notify();
		}
};


template <class T, int nI, int nT>
int prioritySBus<T, nI, nT>::priority(int totalCandidates, bool* thoseRequesting)
{
	// 0 has highest priority
	int found = -1;
	for (int i = totalCandidates - 1; i >= 0; i--){
		if (*(thoseRequesting + i)) found = i;
	}
	return found;
}