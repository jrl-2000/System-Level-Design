#include "interfaceClasses.h"

// data and address type, number of Inititiators
template <class Ti, class Tt, class Ta, int nI> 
class memoryAccess : public requestMem_if<Ti, Ta>, public memRespond_if<Tt, Ta>
{
	int comingFrom;

	Ti incomingData;
	Tt incomingSegments;
	Ta incomingAddress;
	Tt outgoingData;
	bool read;
	bool memoryRequested;
	sc_event memoryCalledFor;
	sc_event memoryCompleted;

	sc_mutex busBusy;
	
	public:
	memoryAccess() : comingFrom(-1), memoryRequested(false) {};
		~memoryAccess() {};

	void requestMem(int initiator, Ti &data, Ta &address, bool rwbar, int delay){
		int burstLength;
		wait(delay, SC_NS);
		busBusy.lock();
		burstLength = data.length() / outgoingData.length();
		for (int j = burstLength; j > 0; j--)
		{
			comingFrom = initiator;
			// Big Endian (Data byte Ends (its LSB) in Bigger address location) 
			if (!rwbar) incomingSegments = data.range(j*outgoingData.length()-1, 
												      (j-1)*outgoingData.length());
			incomingAddress = (address.range(address.length()-1 , 3) ,
											 (sc_lv<3>)(burstLength - j));
			read = rwbar;
			memoryRequested = true;
			memoryCalledFor.notify();
			wait(memoryCompleted);
			if (rwbar) data.range(j*outgoingData.length()-1, 
								  (j-1)*outgoingData.length()) = outgoingData;

				if (rwbar) cout << "Reading " << initiator << ":"
					<< " incomingAddress:" << incomingAddress.to_uint()
					<< ", outgoingData:" << outgoingData << '\n';
				else cout << "Writing " << initiator << ":"
					<< " incomingData:" << incomingSegments
					<< ", incomingAddress:" << incomingAddress.to_uint() << '\n';
		}
		busBusy.unlock();
	}

	void memForward(int &initiator, Tt &data, Ta &address, bool &rwbar){
		if (!memoryRequested) wait(memoryCalledFor);
		memoryRequested = false;
		initiator = comingFrom;
		if (!read) data = incomingSegments;
		address = incomingAddress;
		rwbar = read;
		// Ready for Backward operation
	}
	void memBackward(Tt &data, int delay){
			outgoingData = data;
			wait(delay, SC_NS);
			comingFrom = -1;
			memoryCompleted.notify();
		}
};

