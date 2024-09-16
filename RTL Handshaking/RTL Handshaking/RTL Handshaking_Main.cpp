#include "RTL Handshaking_TB.h"

int sc_main (int argc, char ** argv)
{
	RTLhandshakingTB* HSTB1 = new RTLhandshakingTB ("HandshakingTB");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("Handshaking");

	sc_trace (VCDFile, HSTB1->clk, "Clk");
	sc_trace(VCDFile, HSTB1->go, "GoStart");
	sc_trace(VCDFile, HSTB1->serIn, "SerialIn");
	sc_trace(VCDFile, HSTB1->ready, "Ready4Serial");
	sc_trace (VCDFile, HSTB1->parOut, "Output2Stack");
	sc_trace(VCDFile, HSTB1->push, "Push");

	sc_trace(VCDFile, HSTB1->S2W->collectBits, "collectBits");
	sc_trace(VCDFile, HSTB1->S2W->parReady, "parReady");
    sc_trace(VCDFile, HSTB1->S2W->parAccepted, "parAccepted");
	sc_trace(VCDFile, HSTB1->S2W->countBits, "countBits");
//	sc_trace(VCDFile, HSTB1->S2W->S2Pstate, "S2Pstate");
//	sc_trace(VCDFile, HSTB1->S2W->W2Sstate, "W2Sstate");

//	sc_trace(VCDFile, HSTB1->S2W->gothere, "gothere");
	sc_start(4500, SC_NS);
	sc_close_vcd_trace_file(VCDFile);
	return 0;
}
