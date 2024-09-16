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
	sc_lv<8>* mem; /// Rasoul said so
	
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
		void memRespond(int &initiator, int delay){
			if(!memoryRequested) wait(memoryCalledFor);
			initiator = comingFrom;
			memoryRequested = false;
			
			if (read) outgoingData = mem[incomingAddress.to_uint()];
			else mem[incomingAddress.to_uint()] = incomingData;
			
			wait(delay, SC_NS);
			comingFrom = -1;
			memoryCompleted.notify();
		}
};

