/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q3. SystemC RTL Modeling 
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include <systemc.h>

SC_MODULE(SeqDetector){
	
	sc_in<sc_logic> clk, rst, a;
	sc_out<sc_logic> w;

	enum states { ST0, ST1, ST2, ST3, ST4, ST5 };
	sc_signal<states> Nstate, Pstate;

	SC_CTOR(SeqDetector){

		SC_METHOD (comb_function);
			sensitive << a << Pstate;
		
		SC_METHOD (seq_function); 
			sensitive << clk << rst;
	}

	void comb_function();
	void seq_function();
};