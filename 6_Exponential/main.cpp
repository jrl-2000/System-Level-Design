#include "AVGTB.h"

int sc_main (int argc, char **argv){
	
	AVGTB TB1 ("testbench1");  

	sc_trace_file* vcdfile;
	vcdfile = sc_create_vcd_trace_file("Averaging_test");
	sc_trace(vcdfile, TB1.clk, "clk");
	sc_trace(vcdfile, TB1.rst, "rst");
	sc_trace(vcdfile, TB1.start, "start"); 
	sc_trace(vcdfile, TB1.data, "data");
	sc_trace(vcdfile, TB1.average, "average");
	sc_trace(vcdfile, TB1.ready, "ready");

	sc_start (12000, SC_NS);
	return 0; 
}

