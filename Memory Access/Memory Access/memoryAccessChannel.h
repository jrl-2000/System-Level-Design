#include "interfaceClasses.h"

// data and address type, number of Inititiators
template <class T, int nI> 
class memoryAccess : public requestMem_if<T>, public memRespond_if<T>
{
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
	
	memoryAccess() : comingFrom(-1), memoryRequested(false) {};
	~memoryAccess() {};

	void requestMem(int initiator, T &data, T &address, bool rwbar, int delay){
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

	void memForward(int &initiator, T &data, T &address, bool &rwbar){
		if (!memoryRequested) wait(memoryCalledFor);
		memoryRequested = false;
		initiator = comingFrom;
		if (!read) data = incomingData;
		address = incomingAddress;
		rwbar = read;
		// Ready for Backward operation
	}
	void memBackward(T &data, int delay){
		outgoingData = data;
		wait(delay, SC_NS);
		comingFrom = -1;
		memoryCompleted.notify();
	}
};

