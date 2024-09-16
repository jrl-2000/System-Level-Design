#include <systemc.h>
#include "partsLibrary.h"
#include "adder.h"

SC_MODULE(datapath){
	
	// Port Declaration
	sc_in <sc_logic> clk, start, lddata, ready;
	sc_in <sc_lv<8>> input;
	sc_out <sc_lv<8>> output;
	
	// Signal Declaration
	sc_signal <sc_lv<11>> sum;
	sc_signal <sc_lv<11>> sumreg;
	sc_signal <sc_lv<11>> temp_input;
	
	// Instantiation 
	adder <11>* Add;
	
	SC_CTOR(datapath){
		
		sum = sc_lv<11>("00000000000");
		temp_input = sc_lv<11>("00000000000");
		
		Add = new adder<11>("adder");
			Add->in1(temp_input);
			Add->in2(sum);
			Add->out(sumreg);
		
		SC_METHOD(datapath_assign);
		sensitive << clk << start << input << lddata; 
	}

	void datapath_assign(){
		
		temp_input.write(("000", input->read()));
		sum = (lddata->read() == '1') ? sumreg.read() : (ready->read() == '1') ? sum.read() : "00000000000";
		output = sum.read().range(10, 3);

	}
};