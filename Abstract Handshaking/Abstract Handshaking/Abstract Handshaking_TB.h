#include "Abstract Handshaking.h"

SC_MODULE(AbstractHandshakingTB) {
	sc_signal<sc_logic> clk;
	sc_signal<sc_logic> go, serIn;
	sc_signal<sc_logic> ready;
	sc_signal<sc_lv<8>> parOut;
	sc_signal<sc_logic> push;
	
	AbstractHandshaking* S2W; // Ser to par and Write to stack

	SC_CTOR(AbstractHandshakingTB) {
		S2W = new AbstractHandshaking("Handshaking_TB");
		S2W -> clk(clk);
		S2W -> go(go);
		S2W -> serIn(serIn);
		S2W -> ready(ready);
        S2W -> stackData(parOut);
		S2W -> push(push);

		SC_THREAD(clocking);
		SC_THREAD(serialData);
	}
	void clocking();
	void serialData();
};
