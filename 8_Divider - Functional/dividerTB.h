#include "divider.h"

SC_MODULE(dividerTB)
{
    sc_signal<sc_logic> clk, rst, go, ready;
    sc_signal<sc_lv<8> > A, B, Q, R;
	
	divider<9>* DIV;
	
    SC_CTOR(dividerTB)
    {
        DIV = new divider<9> ("DIV_Instance");
			(*DIV) (A, B, clk, rst, go, Q, R, ready);	

        SC_THREAD(resetting);
		SC_THREAD(clocking);
		SC_THREAD(inGenerating);
		SC_THREAD(displaying);
			sensitive << ready;
        
    }
    void resetting();
	void clocking();
	void inGenerating();
	void displaying();
};

