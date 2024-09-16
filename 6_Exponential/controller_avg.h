#include <systemc.h>

SC_MODULE (controller){

	sc_in  <sc_logic> rst, clk, start;
	sc_out <sc_logic> load1;
	sc_out <sc_logic> load2;
	sc_out <sc_logic> load3;
	sc_out <sc_logic> load4;
	sc_out <sc_logic> load5;
	sc_out <sc_logic> load6;
	sc_out <sc_logic> load7;
	sc_out <sc_logic> load8;
	sc_out <sc_logic> load9;
	sc_out <sc_logic> load10;
	sc_out <sc_logic> ready;
	

	

		
	enum states {INITIALIZE, WAIT_ON_START, COUNT1, COUNT2, COUNT3, COUNT4, COUNT5, COUNT6, COUNT7, COUNT8, COUNT9, COUNT10, READY};
	sc_signal <states> p_state, n_state; 

	SC_CTOR(controller)
	{
		SC_METHOD (comb_S_function);
		sensitive << start << p_state;
		SC_METHOD (comb_O_function);
		sensitive << p_state;
		SC_THREAD (seq_function); 
		sensitive << clk << rst;
	};

	void comb_S_function();
	void comb_O_function();
	void seq_function();
};

