
#pragma once
#include "interfaceClasses.h"

template <class T, int NumOfBuffers>
class multiBufferChannel : public put_if<T>, public get_if<T> {

	bool full[NumOfBuffers]; 
	T saved[NumOfBuffers];
	sc_event put_event[NumOfBuffers];
	sc_event get_event[NumOfBuffers];

	int comingFrom;
	T incomingData;
	T incomingAddress;
	T outgoingData;
	bool read;
	bool memoryRequested;
	sc_event memoryCalledFor;
	sc_event memoryCompleted;

	sc_mutex busBusy;

public:
	multiBufferChannel() : comingFrom(-1), memoryRequested(false) {};
	~multiBufferChannel() {};


	/*multiBufferChannel() {
		for (int i = 0; i < NumOfBuffers; i++) 
			full[i] = false; 
	};
	~multiBufferChannel() {};
	*/
	void put(int targetNum, T data) {
		if (full[targetNum] == true) {
			cout << "Buffer [" << targetNum << "] is full, waiting ... " << "\n"; 
			wait(get_event[targetNum]);
		}
		saved[targetNum] = data;
		full[targetNum] = true;
		put_event[targetNum].notify();
	}
	
	void get(int targetNum, T& data) {
		if (full[targetNum] == false) {
			cout << "Buffer [" << targetNum << "] is empty, waiting ... " << "\n"; 
			wait(put_event[targetNum]);
		}
		data = saved[targetNum];
		full[targetNum] = false;
		get_event[targetNum].notify();
	}
	void requestMem(int initiator, T& data, T& address, bool rwbar, int delay) {
		wait(delay, SC_NS);
		busBusy.lock();
		comingFrom = initiator;
		if (!rwbar) incomingData = data;
		incomingAddress = address;
		read = rwbar;
		memoryRequested = true;
		memoryCalledFor.notify();
		wait(memoryCompleted);
		if (rwbar) data = outgoingData;
		if (rwbar) cout << "Reading " << initiator << ":"
			<< " incomingAddress:" << incomingAddress.to_uint()
			<< ", outgoingData:" << outgoingData << '\n';
		else cout << "Writing " << initiator << ":"
			<< " incomingData:" << incomingData
			<< ", incomingAddress:" << incomingAddress.to_uint() << '\n';
		busBusy.unlock();
	}

	void memForward(int& initiator, T& data, T& address, bool& rwbar) {
		if (!memoryRequested) wait(memoryCalledFor);
		memoryRequested = false;
		initiator = comingFrom;
		if (!read) data = incomingData;
		address = incomingAddress;
		rwbar = read;
		// Ready for Backward operation
	}
	void memBackward(T& data, int delay) {
		outgoingData = data;
		wait(delay, SC_NS);
		comingFrom = -1;
		memoryCompleted.notify();
	}
};