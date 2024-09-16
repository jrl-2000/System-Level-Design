#include "simpleHierarchical.h"

void XORgate::evl()
{
	if (i1->read() == i2->read())
		o1->write(SC_LOGIC_0);
	else
		o1->write(SC_LOGIC_1);
}

void AO2gate::evl()
{
	sc_logic w;
	if (((i1->read() & i2->read()) | (i3->read() & i4->read())) == SC_LOGIC_1)
		o1->write(SC_LOGIC_1); 
	else
		o1->write(SC_LOGIC_0);
}

