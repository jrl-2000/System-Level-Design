#include "serialAddingTB.h"

void serialAddingTB::clockGeneration()
{
	while (true)
	{
		wait(17, SC_NS);
		clock = SC_LOGIC_0;
		wait(17, SC_NS);
		clock = SC_LOGIC_1;
	}
}
void serialAddingTB::resetAssertion()
{
	while (true)
	{
		wait(37, SC_NS);
		reset = SC_LOGIC_0;
		wait(59, SC_NS);
		reset = SC_LOGIC_1; 
		wait(59, SC_NS);
		reset = SC_LOGIC_0;
		wait();
	}
}
void serialAddingTB::ainWaveform()
{
	while (true)
	{
		wait(7, SC_NS);
		ain = SC_LOGIC_0;
		wait(59, SC_NS);
		ain = SC_LOGIC_1;
		wait(83, SC_NS);
		ain = SC_LOGIC_0;
		wait(107, SC_NS);
		ain = SC_LOGIC_1;
		wait();
	}
}
void serialAddingTB::binWaveform()
{
	while (true)
	{
		wait(11, SC_NS);
		bin = SC_LOGIC_0;
		wait(37, SC_NS);
		bin = SC_LOGIC_1;
		wait(101, SC_NS);
		bin = SC_LOGIC_0;
		wait(197, SC_NS);
		bin = SC_LOGIC_1;
		wait();
	}
}
