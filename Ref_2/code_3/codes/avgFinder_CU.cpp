/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "avgFinder_CU.h"

avgFinder_CU::avgFinder_CU(bus& rst_, bus& clk_, bus& start_, bus& ready_,
bus& ldOut_, bus& init0_) :
	rst(&rst_), clk(&clk_), start(&start_), ready(&ready_),
	ldOut(&ldOut_), init0(&init0_) {

	Nstate = 0;
	Pstate = 0;
	inCntr = "0000";
	ldCntr = "0";
	enCntr = '0';
	coCntr = 'X';
	outCntr = "XXXX";

	Cntr = new upCounterRaE(inCntr, *clk, *rst, ldCntr, enCntr, outCntr);
}
void avgFinder_CU::eval() {
	*ready = "0";
	*ldOut = "0";
	*init0 = "0";
	enCntr = "0";

	switch (Pstate) {
	case 0 : // IDLE
		if (*start == "1") Nstate = 1;
		else Nstate = 0;
		break;
	case 1: // INIT
		if (*start == "0") Nstate = 2;
		else Nstate = 1;
		break;
	case 2: // ADD
		if (coCntr == "1") Nstate = 0;
		else Nstate = 2;
		break;
	}

	if (*rst == "1") Pstate = 0;
	else if (*clk == "P") Pstate = Nstate;

	switch (Pstate) {
	case 0: // IDLE
		*ready = "1";
		break;
	case 1: // INIT
		*init0 = "1";
		break;
	case 2: // CMP
		*ldOut = "1";
		enCntr = "1";
		break;
	}

	Cntr->evl();
	coCntr = ((outCntr < "1000") ? "0" : "1");
	cout << "ready = " << *ready << endl;
}