#include <systemc.h>

SC_MODULE (controller){

	sc_in  <sc_logic> clk, rst, start;
	sc_out <sc_logic> lddata, ready;

	int count;
		
	enum states {IDLE, INIT, GETD};
	sc_signal <states> p_state, n_state; 

	SC_CTOR(controller)
	{
		SC_METHOD (state_function);
		sensitive << clk;
		SC_METHOD (output_function);
		sensitive << clk;
		SC_THREAD (seq_function); 
		sensitive << clk << rst;
	};

	void state_function();
	void output_function();
	void seq_function();
};

