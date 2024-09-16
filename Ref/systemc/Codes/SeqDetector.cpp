/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q3. SystemC RTL Modeling
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include "SeqDetector.h"

void SeqDetector::comb_function(){
	w = SC_LOGIC_0;
	Nstate = ST0;

	switch (Pstate.read()){
	case ST0:
		if (a == SC_LOGIC_1) Nstate = ST1;
		else Nstate = ST0; break;
	case ST1:
		if (a == SC_LOGIC_0) Nstate = ST2;
		else Nstate = ST1; break;
	case ST2:
		if (a == SC_LOGIC_1) Nstate = ST3;
		else Nstate = ST0; break;
	case ST3:
		if (a == SC_LOGIC_1) Nstate = ST4;
		else Nstate = ST2; break;
	case ST4:
		if (a == SC_LOGIC_0) Nstate = ST5;
		else Nstate = ST1; break;
	case ST5:
		w = SC_LOGIC_1;
		if (a == SC_LOGIC_1) Nstate = ST3;
		else Nstate = ST0; break;
	}
}

void SeqDetector::seq_function(){
	if (rst == '1') 
		Pstate = ST0;
	else if (clk->event() && clk == '1') 
		Pstate = Nstate;
}
