/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q3. SystemC RTL Modeling 
/*-- by Nooshin Nosrati
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
#pragma once
#include "Testbench.h"

void Testbench::inputing(){
		wait(24, SC_NS);
		a = SC_LOGIC_0;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
		a = SC_LOGIC_0;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
		a = SC_LOGIC_0;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
		a = SC_LOGIC_0;
		wait(14, SC_NS);
		a = SC_LOGIC_0;
		wait(14, SC_NS);
		a = SC_LOGIC_0;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
		a = SC_LOGIC_1;
		wait(14, SC_NS);
}

void Testbench::clocking(){
	while (true)
	{
		clk = sc_logic('0');
		wait (7, SC_NS); 
		clk = sc_logic('1');
		wait (7, SC_NS); 
	}
}

void Testbench::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};

