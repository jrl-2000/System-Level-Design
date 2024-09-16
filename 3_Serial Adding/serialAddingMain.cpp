#include "serialAddingTB.h"

int sc_main(int argc, char **argv)
{
	serialAddingTB* TOP = new serialAddingTB("serialAddingTB_instance");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("serialAdding1");
	sc_trace(VCDFile, TOP->ain, "aInput");
	sc_trace(VCDFile, TOP->bin, "bInput");
	sc_trace(VCDFile, TOP->reset, "reset");
	sc_trace(VCDFile, TOP->clock, "clock");
	sc_trace(VCDFile, TOP->sum, "serialSum");

	sc_trace(VCDFile, TOP->UUT->FA1->i1, "i1_fulladder");
	sc_trace(VCDFile, TOP->UUT->FA1->i2, "i2_fulladder");
	sc_trace(VCDFile, TOP->UUT->FA1->i3, "i3_fulladder");
	sc_trace(VCDFile, TOP->UUT->FA1->o1, "o1_fulladder");
	sc_trace(VCDFile, TOP->UUT->FA1->o2, "o2_fulladder");

	sc_start(4000, SC_NS);
	return 0;
}

