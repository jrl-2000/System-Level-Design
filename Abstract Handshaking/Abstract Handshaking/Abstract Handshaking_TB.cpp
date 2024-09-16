#include "Abstract Handshaking_TB.h"

void AbstractHandshakingTB::clocking() {
	int i;
	clk = SC_LOGIC_0;
	for (i = 0; i<=500; i++){
		wait (29, SC_NS);
		clk = SC_LOGIC_1;
		wait (29, SC_NS);
		clk = SC_LOGIC_0;
	}
}

void AbstractHandshakingTB::serialData() {
	int i, j;
	go = SC_LOGIC_0;
	serIn = SC_LOGIC_0;
	for (i = 1; i < 5; i++){
		if (ready == SC_LOGIC_1){
			wait(31, SC_NS);
			go = SC_LOGIC_1;
			wait(73, SC_NS);
			go = SC_LOGIC_0;
			for (j = 0; j < 7; j++){
				serIn = SC_LOGIC_0;
				wait(17 * i, SC_NS);
				serIn = SC_LOGIC_1;
				wait(23 * i, SC_NS);
				serIn = SC_LOGIC_0;
				wait(31 * i, SC_NS);
				serIn = SC_LOGIC_1;
			}
		}
		else wait(91, SC_NS);
	}
}
