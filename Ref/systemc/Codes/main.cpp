/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q3. SystemC RTL Modeling 
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include "Testbench.h"

int main (int argc, char **argv){
	
	Testbench TOP ("Testbench");  

	sc_trace_file* vcdfile;
	vcdfile = sc_create_vcd_trace_file("SeqDetector");
	sc_trace(vcdfile, TOP.clk, "clk");
	sc_trace(vcdfile, TOP.rst, "rst");
	sc_trace(vcdfile, TOP.a, "a"); 
	sc_trace(vcdfile, TOP.w, "w");

	sc_start (250, SC_NS);
	
	return 0; 
}

