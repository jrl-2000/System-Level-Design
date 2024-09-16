/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "avgFinder_DP.h"
#include "avgFinder_CU.h"

class avgFinder_TOP {

	bus *rst, *clk;
	bus *start,	*ready;
	bus *data, *average;

	avgFinder_DP* DP;
	avgFinder_CU* CU;

	bus ldOut; 
	bus init0; 

public:
	avgFinder_TOP(bus& rst, bus& clk, bus& start, bus& ready, bus& data, bus& average);
	~avgFinder_TOP();
	void eval();
};