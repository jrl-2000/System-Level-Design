#include <systemc.h>

SC_MODULE(RTLhandshaking) {

	sc_in<sc_logic> clk, go;
	sc_out<sc_logic> ready;
	sc_in<sc_logic> serIn;
	sc_out<sc_lv<8>> stackData;
	sc_out<sc_logic> push;

	sc_signal<sc_lv<8>> collectBits;
	sc_signal<sc_logic> parAccepted, parReady;

	// Serial-to-Parallel internals
	enum S2PstateType {go1Wait, go0Wait, count8Bits, got8Bits};
	sc_signal<S2PstateType> S2Pstate;
	sc_signal<sc_lv<3>> countBits;

	// Write-to-Stack internals
	enum W2SstateType {par1Wait, par0Wait, pushData};
	sc_signal<W2SstateType> W2Sstate;

	SC_CTOR(RTLhandshaking) {
		SC_METHOD(S2Ptransition);
			sensitive << clk;
		SC_METHOD(S2Psignals);
			sensitive << S2Pstate;
		SC_METHOD(W2Stransition);
			sensitive << clk;
		SC_METHOD(W2Ssignals);
			sensitive << W2Sstate;
	}
	void S2Ptransition();
	void S2Psignals();
	void W2Stransition();
	void W2Ssignals();
};
