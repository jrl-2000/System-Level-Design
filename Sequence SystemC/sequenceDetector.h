#include <systemc.h>

SC_MODULE(sequenceDetector)
{
	sc_in<sc_logic> a, rst, clk;
	sc_out<sc_logic> w;

	enum states { ST0, ST1, ST2, ST3, ST4, ST5 };

	sc_signal<states> Nstate, Pstate;

	SC_CTOR(sequenceDetector) 
	{
		Pstate.write(ST0);
		Nstate.write(ST0);

		SC_METHOD(evlCombinational);
			sensitive << a << Pstate;

		SC_METHOD(evlSequential);
			sensitive << clk << rst;
	}

	void evlCombinational();
	void evlSequential();
};

