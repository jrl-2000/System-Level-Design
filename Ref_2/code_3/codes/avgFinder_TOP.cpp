/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "avgFinder_TOP.h"

avgFinder_TOP::avgFinder_TOP(bus& rst_, bus& clk_, bus& start_, bus& ready_, bus& data_, bus& average_):
	rst(&rst_), clk(&clk_), start(&start_), ready(&ready_), data(&data_), average(&average_) {
	
	ldOut = 'X';
	init0 = 'X';

	DP = new avgFinder_DP(*rst, *clk, *data, *average, ldOut, init0);
	CU = new avgFinder_CU(*rst, *clk, *start, *ready, ldOut, init0);
}

void avgFinder_TOP::eval() {
	CU->eval();
	DP->eval();
}