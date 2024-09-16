#include "sequenceDetector.h"

sequenceDetector::sequenceDetector (bus& rst, bus& clk, bus& a, bus& w)
{
	this->rst = &rst; this->clk = &clk; this->a = &a; this->w = &w;
	Nstate = 0;
	Pstate = 0;
	}

void sequenceDetector::evl () {
	*w = "0";

	// 10110
	switch (Pstate){
		case 0: 
			if(*a == "1") Nstate = 1;
			else Nstate = 0; break;
		case 1:
			if (*a == "1") Nstate = 1;
			else Nstate = 2; break;
		case 2:
			if(*a == "1") Nstate = 3;
			else Nstate = 0; break;
		case 3: 
			if(*a == "1") Nstate = 4;
			else Nstate = 2; break;
		case 4: 
			if(*a == "1") Nstate = 1;
			else Nstate = 5; break;
		case 5: 
			if (*a == "1") Nstate = 3;
			else Nstate = 0; break;
	}

	if (*rst == "1") Pstate = 0;
	else if (*clk == "P") Pstate = Nstate;	
	
	if (Pstate == 5) *w = "1";
	else *w = "0";
}
