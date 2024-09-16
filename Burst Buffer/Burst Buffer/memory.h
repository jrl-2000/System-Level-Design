#include <systemc.h>

SC_MODULE (memory) {
	sc_in_rv<16> addressBus;
	sc_inout_rv<8> dataBus;
	sc_in_resolved rwbar, cs;
	sc_out_resolved memReady;
	int memActivePart, memDelay;
	sc_lv<8> *mem;

	SC_HAS_PROCESS(memory);
	
	memory(sc_module_name NAME, int P=1024, int D=9);
	~memory() {delete []mem;}

	void memReadWrite();
};