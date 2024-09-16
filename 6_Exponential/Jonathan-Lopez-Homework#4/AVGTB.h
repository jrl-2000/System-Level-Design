#include "AVGDesign.h"

SC_MODULE(AVGTB){
	sc_signal <sc_logic> clk, rst, start; 
	sc_signal <sc_lv<8> > data;
	sc_signal < sc_lv<8> > average; 
	sc_signal <sc_logic> ready;
	
	AVG* AVG1; 

	SC_CTOR (AVGTB){
		AVG1= new AVG ("Averaging_1"); 
			AVG1->clk(clk); 
			AVG1->rst(rst); 
			AVG1->start(start); 
			AVG1->data(data); 
			AVG1->average(average);
			AVG1->ready(ready);

		//
		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking); 
		SC_METHOD(displaying);
			sensitive <<ready.posedge_event();
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
	void displaying(); 
}; 
