#include "simpleHierarchical.h"

SC_MODULE(serialAddingTB)
{
	sc_signal<sc_logic> ain, bin, reset, clock;
	sc_signal<sc_logic> sum;

	serialAdding* UUT;
	
	SC_CTOR(serialAddingTB)
	{
		UUT = new serialAdding("serialAdding_instance");
			(*UUT) (ain, bin, reset, clock, sum);
		SC_THREAD(clockGeneration);
		SC_THREAD(resetAssertion);
		SC_THREAD(ainWaveform);
			sensitive << clock.posedge_event();
		SC_THREAD(binWaveform);
			sensitive << clock.posedge_event();
	}
	void clockGeneration();
	void resetAssertion();
	void ainWaveform();
	void binWaveform();
};
