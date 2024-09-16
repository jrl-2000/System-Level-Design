#include "multiplier.h"

SC_MODULE(multiplierTB)
{
    sc_signal<sc_logic> clk, rst, go, ready;
    sc_signal<sc_lv<8> > A, B;
	sc_signal<sc_lv<16> > Result;
	
	multiplier<12>* MUL;
	
    SC_CTOR(multiplierTB)
    {
        MUL = new multiplier<12> ("MUL_Instance");
			(*MUL) (A, B, clk, rst, go, Result, ready);	

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
