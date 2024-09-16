#include "simpleHierarchical.h"

int sc_main(int argc, char **argv)
{
	sc_signal<sc_logic>	aData;
	sc_signal<sc_logic>	bData;
	sc_signal<sc_logic>	cData;
	sc_signal<sc_logic>	cOut;
	sc_signal<sc_logic>	sOut;

	oneBitAdder* FA1 = new oneBitAdder("FA1_instance");  
		(*FA1) (aData, bData, cData, cOut, sOut);

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("simpleHierarchical");
		sc_trace(VCDFile, aData, "aIn");
		sc_trace(VCDFile, bData, "bIn");
		sc_trace(VCDFile, cData, "carryIn");
		sc_trace(VCDFile, cOut, "carryOut");
		sc_trace(VCDFile, sOut, "sumOut");

	sc_int<3> intData;
	sc_lv<3> abcData;

	sc_start(15, SC_NS);
	cout << "Simulation starts at: " << sc_time_stamp() << '\n';

	intData = 0;
	int ij=0;	
	do {
		abcData = intData;
		aData = abcData[2]; 
		bData = abcData[1]; 
		cData = abcData[0];
		sc_start(15, SC_NS);
		cout << "At time: " << sc_time_stamp();
		cout << "Inputs a, b, ci: " << abcData;
		cout << "; Outputs co, su: " << cOut << " " << sOut << '\n';
		intData = intData + 1;
		sc_start(50, SC_NS);
	} while (++ij < 40);

	sc_start(100,SC_NS);
	return 0;
}
