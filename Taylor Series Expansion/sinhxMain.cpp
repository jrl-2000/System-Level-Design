#include "sinhxTB.h"

int sc_main (int argc , char *argv[])
{
	HyperbolicSineTB* TOP = new HyperbolicSineTB("exponentialTB_Instance");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("Hyperbolic");
	sc_trace(VCDFile, TOP->inHSU, "inHSU");
	sc_trace(VCDFile, TOP->clk, "clk");
	sc_trace(VCDFile, TOP->rst, "rst");
	sc_trace(VCDFile, TOP->startHSU, "start HSU");
	sc_trace(VCDFile, TOP->readyHSU, "ready HSU");
	sc_trace(VCDFile, TOP->outHSU, "outHSU");

    sc_start(2000, SC_NS);
    return 0;
}
