#include "simpleTransport.h"

SC_MODULE (simpleTransport_TB) {

	transmitter* TRS1;
	receiver* RCV1; 

	SC_CTOR(simpleTransport_TB) {
		RCV1 = new receiver("receiver");
		TRS1 = new transmitter("transmitter");
			TRS1->out(*RCV1->insideTargetChannel);
	}
};

