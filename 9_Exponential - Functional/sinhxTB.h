#include "sinhx.h"

SC_MODULE(HyperbolicSineTB)
{
    sc_signal<sc_logic> clk, rst, startHSU, readyHSU;
    sc_signal<float> inHSU, outHSU;

	HyperbolicSine<24, 16>* HYBS;

    SC_CTOR(HyperbolicSineTB)
    {
		HYBS = new HyperbolicSine<24, 16> ("HYBS_Instance");
			(*HYBS) (inHSU, clk, rst, startHSU, outHSU, readyHSU);

        SC_THREAD(resetting);
		SC_THREAD(clocking);
		SC_THREAD(inGenerating);
		SC_THREAD(displaying);
			sensitive << readyHSU;

    }
    void resetting();
	void clocking();
	void inGenerating();
	void displaying();
};
