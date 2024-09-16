#include <iostream>
#include <systemc.h>

template <int NumClk, int N>
SC_MODULE (HyperbolicSine)
{
    sc_in<float> inHSU;
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> startHSU;

	sc_out<float> outHSU;
    sc_out<sc_logic> readyHSU;

	sc_signal<float> inHSU_reg;

    SC_CTOR(HyperbolicSine)
	{
        SC_THREAD(operation)
            sensitive << clk << rst;
    }
    void operation();
};


template <int NumClk, int N>
void HyperbolicSine<NumClk, N>::operation()
{
	while (true)
	{

		float term = 1.0;
		
		float factorial = 1.0;
		int j = 0;

		if (rst == '1')
		{
			readyHSU = SC_LOGIC_0;
			outHSU = 0;
		}

		else if ((clk == '1') && (clk->event()))
		{
			readyHSU = SC_LOGIC_1;
			if (startHSU == '1')
			{
				readyHSU = SC_LOGIC_0;
			}
			else if (startHSU == '0') {
				readyHSU = SC_LOGIC_1;
				outHSU = 0;

				inHSU_reg = inHSU->read();
				wait(clk->posedge_event());

				for (int i = 0; i < 16; i++) {

					j = (2 * i) + 1;

					if (j == 0 || j == 1) {
						factorial = 1;
					}
					for (int j = 2; j <= 15; ++j) {
						factorial *= j;
					}
					//std::pow(inHSU_reg.read(), ((2*i)+1));
					//(inHSU_reg.read() ^ (2 * i + 1)
					term = term + ((std::pow(inHSU_reg.read(), ((2 * i) + 1))) / (factorial));
				}

				for (int i = 0; i < NumClk - 1; i++) {
				wait(clk->posedge_event());
				readyHSU = SC_LOGIC_0;
				}
				readyHSU = SC_LOGIC_0;
				outHSU = term;
			}
		}
		wait();
	}
}

