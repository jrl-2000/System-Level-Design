#include "interfaceClasses.h"
#pragma once

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

template <int N>
class buffer : public Buffer_put_if, public Buffer_get_if
{
	bool full;
	sc_lv<8> saved;
	int size = N;
	sc_event put_event, get_event;
public:
	buffer() : full(false) {};
	~buffer() {};
	void Buffer_put(sc_lv<8> data);
	void Buffer_get(sc_lv<8>& data);

};
