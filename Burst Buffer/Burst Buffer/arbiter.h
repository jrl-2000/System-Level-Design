#include <systemc.h>

SC_MODULE(arbiter) {
	sc_in<sc_lv<4>> request;
	sc_out<sc_lv<4>> grant;
	int clockDelay;
	sc_lv<4> granted;

	SC_HAS_PROCESS(arbiter);
	arbiter(sc_module_name NAME, int D) : sc_module(NAME), clockDelay(D) {
		SC_THREAD(arbitration);
		sensitive << request;
	}
	~arbiter() {}

	void arbitration();
};