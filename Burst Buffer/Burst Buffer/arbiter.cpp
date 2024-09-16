#include "arbiter.h"

void arbiter::arbitration() {
	while (1) {
		wait(clockDelay, SC_NS);
		for (int i = 3; i >= 0; i--){
			if (request->read()[i] == SC_LOGIC_1) granted[i] = SC_LOGIC_1;
			else granted[i] = SC_LOGIC_0;
		}
		grant->write(granted);
		wait();
	}
}
