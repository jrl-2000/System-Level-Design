#include "sequenceDetector.h"

SC_MODULE(sequenceDetectorTB)
{
	sc_signal<sc_logic> a, reset, clock;
	sc_signal<sc_logic> w;

	sequenceDetector* UUT;

	SC_CTOR(sequenceDetectorTB)
	{
		UUT = new sequenceDetector ("sequenceDetector_instance");
			UUT->a(a);
			UUT->rst(reset);
			UUT->clk(clock);
			UUT->w(w);
	
		SC_THREAD(clockGeneration);
		SC_THREAD(resetAssertion);
		SC_THREAD(inWaveform);
	}
	void clockGeneration();
	void resetAssertion();
	void inWaveform();
};
