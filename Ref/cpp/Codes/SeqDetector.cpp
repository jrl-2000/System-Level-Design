/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q2. C/C++ RTL Design & Modeling
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "SeqDetector.h"

SeqDetector::SeqDetector(bus& rst_, bus& clk_, bus& a_, bus& w_) :
	rst(&rst_), clk(&clk_), a(&a_), w(&w_) {

	Nstate = 0;
	Pstate = 0;
	}

void SeqDetector::eval() {
	*w = "0";
	Nstate = 0;

	switch (Pstate) { 
	case 0: // Reset
		if (*a == "1") Nstate = 1;
		else Nstate = 0;
		break;
	case 1: // Got 1
		if (*a == "0") Nstate = 2;
		else Nstate = 1;
		break;
	case 2: // Got 10
		if (*a == "1") Nstate = 3;
		else Nstate = 0;
		break;
	case 3: // Got 101
		if (*a == "1") Nstate = 4;
		else Nstate = 2;
		break;
	case 4: // Got 1011
		if (*a == "0") Nstate = 5;
		else Nstate = 1;
		break;
	case 5: // Got 10110
		if (*a == "1") Nstate = 3;
		else Nstate = 0;
		break;
	default: 
		Nstate = 0;
		break;
	}

	if (*rst == "1") Pstate = 0;
	else if (*clk == "P") Pstate = Nstate;

	if (Pstate == 5) *w = "1";
	else *w = "0";
}