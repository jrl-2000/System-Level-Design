/*
#include "exponential.h"

template <int NumClk, int N>
void exponential<NumClk, N>::operation()
{
	while (true)
	{
		float term = 1;
		float exp = 1;

        if (rst == '1')
		{
			ready = SC_LOGIC_0;
			RBus = 0;
		}

		else if ((clk == '1') && (clk->event()))
		{
			if (go == '1')
			{
				ready = SC_LOGIC_0;
				RBus = 0;

				XBus_reg = XBus->read();
				wait(clk->posedge_event());

				for (int i=1; i<N; i++){
					term = term * XBus_reg.read();
					term = term * (1/float(i));
					exp = exp + term;
				}

				for(int i = 0; i < NumClk-1; i++)
					wait(clk->posedge_event());

				ready = SC_LOGIC_1;
				RBus = exp;
			}
		}
		wait();
    }
}
*/
