/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "classVectorPrimitives.h"

class avgFinder_DP {

	bus *rst, *clk;
	bus *data, *average;
	bus *ldOut, *init0;
	
	dRegisterRaE* regOut;
	Adder* add;
	
	bus outRegData;
	bus outAdd;
	bus inpAdd;
	bus zeros;
	bus ci;
	bus co;

public:
	avgFinder_DP(bus& rst, bus& clk, bus& data, bus& average, bus& ldOut, bus& init0);
	~avgFinder_DP();
	void eval();
};