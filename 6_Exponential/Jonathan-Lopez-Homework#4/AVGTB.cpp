#include "AVGTB.h"

void AVGTB::inputing(){

		// Full Pulse on start
		start = SC_LOGIC_0;
		wait(100, SC_NS);
		start = SC_LOGIC_1;
		wait(100, SC_NS);
		start = SC_LOGIC_0;

		
		// Data Coming in every posedge TEST #1
		data = "00000001"; // Data 0
		wait(100, SC_NS);
		data = "00000001"; // Data 1
		wait(100, SC_NS);
		data = "00000001"; // Data 2
		wait(100, SC_NS);
		data = "00000001"; // Data 3
		wait(100, SC_NS);
		data = "00000001"; // Data 4
		wait(100, SC_NS);
		data = "00000001"; // Data 5
		wait(100, SC_NS);
		data = "00000001"; // Data 6
		wait(100, SC_NS);
		data = "00000001"; // Data 7
		wait(100, SC_NS);
		
		/*
		// Data Coming in every posedge TEST #2
		data = "11111111"; // Data 0
		wait(100, SC_NS);
		data = "11111111"; // Data 1
		wait(100, SC_NS);
		data = "11111111"; // Data 2
		wait(100, SC_NS);
		data = "11111111"; // Data 3
		wait(100, SC_NS);
		data = "11111111"; // Data 4
		wait(100, SC_NS);
		data = "11111111"; // Data 5
		wait(100, SC_NS);
		data = "11111111"; // Data 6
		wait(100, SC_NS);
		data = "11111111"; // Data 7
		wait(100, SC_NS);
		*/
		/*
		// Data Coming in every posedge TEST #3
		data = "00011101"; // Data 0
		wait(100, SC_NS);
		data = "00010011"; // Data 1
		wait(100, SC_NS);
		data = "00011100"; // Data 2
		wait(100, SC_NS);
		data = "01101110"; // Data 3
		wait(100, SC_NS);
		data = "10000001"; // Data 4
		wait(100, SC_NS);
		data = "00100111"; // Data 5
		wait(100, SC_NS);
		data = "10111101"; // Data 6
		wait(100, SC_NS);
		data = "11001111"; // Data 7
		wait(100, SC_NS);
		*/
		/*
		// Data Coming in every posedge TEST #4
		data = "00100101"; // Data 0
		wait(100, SC_NS);
		data = "01001001"; // Data 1
		wait(100, SC_NS);
		data = "00110101"; // Data 2
		wait(100, SC_NS);
		data = "00101100"; // Data 3
		wait(100, SC_NS);
		data = "10000000"; // Data 4
		wait(100, SC_NS);
		data = "10111110"; // Data 5
		wait(100, SC_NS);
		data = "01011111"; // Data 6
		wait(100, SC_NS);
		data = "01010100"; // Data 7
		wait(100, SC_NS);
		*/


		// Wait
		wait(1000, SC_NS);

}

void AVGTB::clocking(){
	int i; 
	clk = sc_logic('1'); 
	for (i=0; i <=50; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}

void AVGTB::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};

void AVGTB::displaying(){
	cout << "End" <<endl; 
}


