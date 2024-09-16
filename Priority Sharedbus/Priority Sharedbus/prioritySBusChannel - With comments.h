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
			//wait(delay, SC_NS);
//cout << "INI before locked " << initiator << " " << target << " " << data << '\n';

			requestingI[initiator] = true;
cout << ">>>>>>>> initiator "<< initiator << " placed in queue, queue is: ";
for (int j = 0; j <= 3; j++) cout << requestingI[j]; cout << "  <<<<<<<<\n";
			while (busBusy||(initiator != priority(nI, requestingI)))
			{
				wait(busReleased);
			}
			requestingI[initiator] = false;
cout << ">>>>>>>> granted " << initiator << ", queue is reduced to: ";
for (int j = 0; j <= 3; j++) cout << requestingI[j]; cout << " <<<<<<<<\n";
			busBusy = true;

//cout << "Bus locked by " << initiator <<'\n';

			comingFrom = initiator;
			goingTo = target;
			dataPlaced = data;

//cout << "INI after lock before notify " << initiator << " " << target << " " << data << '\n';

			dataAvailable[target].notify();

//cout << "INI after notify " << initiator << " " << target << " " << data << '\n';

			wait(dataReceived[target]);
			busBusy = false;
			busReleased.notify();
		}
		void get(int &initiator, int target, T &data, int delay){

//cout << "TAR before wait " << comingFrom << " " << goingTo << " " << target <<" "<< data << '\n';


			if (goingTo != target) wait(dataAvailable[target]);
			initiator = comingFrom;
			data = dataPlaced;
			wait(delay, SC_NS);
//cout << "TAR after wait " << initiator << " " << target << " " << data << '\n';

			comingFrom = -1;
			goingTo = -1; // prevent multiple gets of same data
			dataReceived[target].notify();

//cout << "TAR after notify " << comingFrom << " " << goingTo << " " << data << '\n';
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