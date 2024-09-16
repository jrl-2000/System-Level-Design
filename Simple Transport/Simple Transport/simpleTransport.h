#include "channelTransport.h"

class transmitter : public sc_module {
public:
	sc_port<transport_if> out;

	SC_CTOR(transmitter) {
		SC_THREAD (transportingOut);
	}
	void transportingOut();	
};

class receiver : public sc_module {
public:
	sc_export<transport_if> in;
	channelTransport* insideTargetChannel;

	SC_CTOR(receiver) {
		insideTargetChannel = new channelTransport;
		in(*insideTargetChannel);
		SC_THREAD(transportingIn);
    }
	void transportingIn();
};
