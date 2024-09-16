#include "datapath.h"
#include "controller.h"

SC_MODULE(AVG){
	sc_in <sc_logic> clk, rst, start; 
	sc_in <sc_lv<8> > input;
	sc_out < sc_lv<8>>  output; 
	sc_out <sc_logic> ready;
	sc_signal <sc_logic> lddata;

	datapath* DP; 
	controller* CNTRL; 

	SC_CTOR(AVG){
		DP = new datapath("dp"); 
			(*DP) (clk, start, lddata, ready, input, output);	

		CNTRL = new controller ("cu"); 
			(*CNTRL) (clk, rst, start, lddata, ready);
		}
};

