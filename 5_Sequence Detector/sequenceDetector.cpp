#include "sequenceDetector.h"

void sequenceDetector::evlCombinational()
{
	w = SC_LOGIC_0;
	Nstate = ST0;

	switch (Pstate.read()){
	case ST0:
		if (a == SC_LOGIC_1) Nstate = ST1;
		else Nstate = ST0; break;
	case ST1:
		if (a == SC_LOGIC_1) Nstate = ST1;
		else Nstate = ST2; break;
	case ST2:
		if (a == SC_LOGIC_1) Nstate = ST3;
		else Nstate = ST0; break;
	case ST3:
		if (a == SC_LOGIC_1) Nstate = ST4;
		else Nstate = ST2; break;
	case ST4:
		if (a == SC_LOGIC_1) Nstate = ST1;
		else Nstate = ST5; break;
	case ST5:
		if (a == SC_LOGIC_1) Nstate = ST3;
		else Nstate = ST0; break;
	}

	if (Pstate == ST5) w = SC_LOGIC_1;
}

void sequenceDetector::evlSequential()
{
	if (rst == SC_LOGIC_1) Pstate = ST0;
	else if (clk->event() && clk == SC_LOGIC_1) Pstate = Nstate;
}
