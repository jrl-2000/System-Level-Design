#include "sequenceDetectorTB.h"

int sc_main(int argc, char **argv)
{
	sequenceDetectorTB* TOP = new sequenceDetectorTB("sequenceDetectorTB_instance");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("sequenceDetector");
	sc_trace(VCDFile, TOP->a, "a");
	sc_trace(VCDFile, TOP->reset, "reset");
	sc_trace(VCDFile, TOP->clock, "clock");
	sc_trace(VCDFile, TOP->w, "w");

	sc_start(4000, SC_NS);
	return 0;
}
