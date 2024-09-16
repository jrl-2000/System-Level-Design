#include "AVG.h"

SC_MODULE(TB){
	sc_signal <sc_logic> clk, rst, start; 
	sc_signal <sc_lv<8>> data;
	sc_signal <sc_lv<8>> average; 
	sc_signal <sc_logic> ready;
	
	AVG* Avg1; 

	SC_CTOR (TB){
		Avg1= new AVG ("avg_tst"); 
			Avg1->clk(clk); 
			Avg1->rst(rst); 
			Avg1->start(start);
			Avg1->input(data);
			Avg1->output(average); 
			Avg1->ready(ready); 
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
