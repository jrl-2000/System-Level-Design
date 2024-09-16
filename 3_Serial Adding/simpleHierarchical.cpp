#include "simpleHierarchical.h"

void XORgate::evl()
{
	while (true)
	{
		if (i1->read() == i2->read())
		{
			wait(Td);
			o1->write(SC_LOGIC_0);
		}
		else
		{
			wait(Td);
			o1->write(SC_LOGIC_1);
		}
		wait();
	}
}

void AO2gate::evl()
{
	while (true)
	{
		if (((i1->read() & i2->read()) | (i3->read() & i4->read())) == SC_LOGIC_1)
		{
			wait(Td);
			o1->write(SC_LOGIC_1);
		}
		else
		{
			wait(Td);
			o1->write(SC_LOGIC_0);
		}
		wait();
	}
}

void Dflipflop::evl()
{
	while (true)
	{	
		if (rst == SC_LOGIC_1) {
			wait(0.6, SC_NS);
			Q = SC_LOGIC_0;
		}
		else if (clk->event() && (clk == '1')) {
			wait(0.6, SC_NS);
			Q = D;
		}
		wait();
	}
}
