/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q3. SystemC RTL Modeling 
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include "SeqDetector.h"

SC_MODULE(Testbench){
	sc_signal <sc_logic> clk, rst, a, w; 
	
	SeqDetector* UUT;

	SC_CTOR(Testbench){
		UUT = new SeqDetector("SeqDetector");
		(*UUT) (clk, rst, a, w);

		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking); 
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
}; 
