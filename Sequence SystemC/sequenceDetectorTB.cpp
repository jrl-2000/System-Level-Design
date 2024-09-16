#include "sequenceDetectorTB.h"

void sequenceDetectorTB::clockGeneration()
{
	while (true)
	{
		wait(5, SC_NS);
		clock = SC_LOGIC_0;
		wait(5, SC_NS);
		clock = SC_LOGIC_1;
	}
}
void sequenceDetectorTB::resetAssertion()
{
	while (true)
	{
		wait(20, SC_NS);
		reset = SC_LOGIC_0;
		wait(10, SC_NS);
		reset = SC_LOGIC_1;
		wait(10, SC_NS);
		reset = SC_LOGIC_0;
		wait();
	}
}
void sequenceDetectorTB::inWaveform()
{
	while (true)
	{
		a = SC_LOGIC_0; // Init
		wait(60, SC_NS);
		a = SC_LOGIC_1;
		wait(10, SC_NS);
		a = SC_LOGIC_0;
		wait(10, SC_NS);
		a = SC_LOGIC_1;
		wait(10, SC_NS);
		a = SC_LOGIC_1;
		wait(10, SC_NS);
		a = SC_LOGIC_1;
		wait(10, SC_NS);
		a = SC_LOGIC_0;
		wait(10, SC_NS);
		a = SC_LOGIC_1;
		wait(10, SC_NS);
		a = SC_LOGIC_1;
		wait(10, SC_NS);
		a = SC_LOGIC_0;

	}
}
