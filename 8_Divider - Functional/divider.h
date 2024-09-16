#include <iostream>
#include <systemc.h>
using namespace std;

template <int NumClk>
SC_MODULE(divider)
{
    sc_in<sc_lv<8> > A;
    sc_in<sc_lv<8> > B;
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> go;
	
	sc_out<sc_lv<8> > Q;
	sc_out<sc_lv<8> > R;
    sc_out<sc_logic> ready;
	
    SC_CTOR(divider)
	{
        SC_THREAD(operation)
            sensitive << clk << rst;
    }
    void operation();   
};

template <int NumClk>
void divider<NumClk>::operation()
{
	sc_lv<8> Q_var;
	
	while (true)
	{
        if (rst == '1')
		{
			ready = SC_LOGIC_0;
			Q = "00000000";
			R = "00000000";
		}
		
		else if ((clk == '1') && (clk->event()))
		{
			if (go == '1') 
			{
				ready = SC_LOGIC_0;
				Q = "XXXXXXXX";
				R = "XXXXXXXX";

				for(int i = 0; i < NumClk; i++)
					wait(clk->posedge_event());

				ready = SC_LOGIC_1;
				Q_var = A->read().to_uint() / B->read().to_uint();
				Q = Q_var;
				R = (A->read().to_uint()) - (B->read().to_uint() * Q_var.to_uint());
			}
		}
		wait();
    }   
}


