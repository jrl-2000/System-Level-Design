#include <iostream>
#include <systemc.h>
using namespace std;

template <int NumClk>
SC_MODULE(multiplier)
{
    sc_in<sc_lv<8> > A;
    sc_in<sc_lv<8> > B;
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> go;
	
	sc_out<sc_lv<16> > Result;
    sc_out<sc_logic> ready;
	
    SC_CTOR(multiplier)
	{
        SC_THREAD(operation)
            sensitive << clk << rst;
    }
    void operation();   
};

template <int NumClk>
void multiplier<NumClk>::operation()
{
	while (true)
	{
        if (rst == '1')
		{
			ready = SC_LOGIC_0;
			Result = "0000000000000000";
		}
		
		else if ((clk == '1') && (clk->event()))
		{
			if (go == '1') 
			{
				ready = SC_LOGIC_0;
				Result = "XXXXXXXXXXXXXXXX";

				for(int i = 0; i < NumClk; i++)
					wait(clk->posedge_event());

				ready = SC_LOGIC_1;
				Result = A->read().to_uint() * B->read().to_uint();
			}
		}
		wait();
    }   
}

