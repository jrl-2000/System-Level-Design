/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "classVectorPrimitives.h"

class avgFinder_CU {

	bus *rst, *clk;
	bus *start,	*ready;
	bus *ldOut, *init0;     //go to the datapath

	upCounterRaE* Cntr;
	
	int Nstate, Pstate;
	bus inCntr, ldCntr, enCntr, coCntr;
	bus outCntr;

public:
	avgFinder_CU(bus& rst, bus& clk, bus& start, bus& ready,
		bus& ldOut, bus& init0);
	~avgFinder_CU();
	void eval();

};