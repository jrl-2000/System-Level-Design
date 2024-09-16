/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q2. C/C++ RTL Design & Modeling
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "classVectorPrimitives.h"

class SeqDetector {

	bus *rst, *clk, *a;
	bus *w;
	
	int Nstate, Pstate;

public:
	SeqDetector(bus& rst, bus& clk, bus& a, bus& w);
	~SeqDetector();
	void eval();

};