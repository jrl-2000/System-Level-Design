#include <systemc.h>

SC_MODULE(AbstractHandshaking) {

	sc_in<sc_logic> clk, go;
	sc_out<sc_logic> ready;
	sc_in<sc_logic> serIn;
	sc_out<sc_lv<8>> stackData;
	sc_out<sc_logic> push;

	sc_lv<8> collectBits;
	sc_event parAccepted_ev, parReady_ev;

	SC_CTOR(AbstractHandshaking) {
		SC_THREAD(S2Phandler);
			sensitive << clk.pos();
		SC_THREAD(W2Shandler);
			sensitive << clk.pos();
	}
	void S2Phandler();
	void W2Shandler();
};
