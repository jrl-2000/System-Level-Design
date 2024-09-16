#include "datapath_avg.h"
#include "controller_avg.h"

SC_MODULE(AVG){
	sc_in <sc_logic> clk, rst, start; 
	sc_in <sc_lv<8> > data;
	sc_out < sc_lv<8>>  average; 
	sc_out <sc_logic> ready;

	sc_signal <sc_logic> load1;
	sc_signal <sc_logic> load2;
	sc_signal <sc_logic> load3;
	sc_signal <sc_logic> load4;
	sc_signal <sc_logic> load5;
	sc_signal <sc_logic> load6;
	sc_signal <sc_logic> load7;
	sc_signal <sc_logic> load8;
	sc_signal <sc_logic> load9;
	sc_signal <sc_logic> load10;


	//sc_signal <sc_lv<4>> cntr;

	
	datapath* DP; 
	controller* CNTRL; 

	SC_CTOR(AVG){
		DP = new datapath("Datapath"); 
			(*DP) (clk, rst, load1, load2, load3, load4, load5, load6, load7, load8, load9, load10, data, average);

		CNTRL = new controller ("Controller"); 
			(*CNTRL) (rst, clk, start, load1, load2, load3, load4, load5, load6, load7, load8, load9, load10, ready);
		}
};

