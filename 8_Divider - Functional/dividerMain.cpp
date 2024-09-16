#include "dividerTB.h"

int sc_main (int argc , char *argv[])
{
	dividerTB* TOP = new dividerTB ("dividerTB_Instance");
   
	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("Divider");
	sc_trace(VCDFile, TOP->A, "A");
	sc_trace(VCDFile, TOP->B, "B");
	sc_trace(VCDFile, TOP->clk, "clk");
	sc_trace(VCDFile, TOP->rst, "rst");
	sc_trace(VCDFile, TOP->go, "go");
	sc_trace(VCDFile, TOP->ready, "ready");
	sc_trace(VCDFile, TOP->Q, "Q");
	sc_trace(VCDFile, TOP->R, "R");

    sc_start(2000, SC_NS);
    return 0;
}
