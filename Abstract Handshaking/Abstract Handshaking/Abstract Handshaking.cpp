#include "Abstract Handshaking.h"

void AbstractHandshaking::S2Phandler() {
	int i;
	ready = SC_LOGIC_0;
	while (1){
		ready = SC_LOGIC_1;
		while (go != '1') wait();
		ready = SC_LOGIC_0;
		while (go != '0') wait();
		for (i = 0; i < 8; i++){
			wait();
			collectBits[i] = serIn;
		}
		wait();
		parReady_ev.notify();
		wait(parAccepted_ev);
	}
}

void AbstractHandshaking::W2Shandler() {
	push = SC_LOGIC_0;
	stackData = 0;
	while (1){
		wait(parReady_ev);
		stackData = collectBits;
		wait();
		parAccepted_ev.notify();
		wait();
		push = SC_LOGIC_1;
		wait();
		push = SC_LOGIC_0;
		stackData = 0;
	}
}
