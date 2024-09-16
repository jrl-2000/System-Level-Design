#include <systemc.h>

SC_MODULE(XORgate)
{
	sc_in<sc_logic> i1, i2;
	sc_out<sc_logic> o1;

	sc_time Td; 
	SC_HAS_PROCESS(XORgate);
	XORgate::XORgate(sc_module_name, sc_time delay)
	{
		Td = delay;
		SC_THREAD(evl);
		sensitive << i1 << i2;
	}
	void evl();
};

SC_MODULE(AO2gate)
{
	sc_in<sc_logic> i1, i2, i3, i4;
	sc_out<sc_logic> o1;

	sc_time Td; 
	SC_HAS_PROCESS(AO2gate);
	AO2gate::AO2gate(sc_module_name, sc_time delay)
	{
		Td = delay;
		SC_THREAD(evl);
		sensitive << i1 << i2 << i3 << i4;
	}
	void evl();
};

SC_MODULE(oneBitAdder)
{
	sc_in<sc_logic> i1, i2, i3;
	sc_out<sc_logic> o1, o2; // Carry, Sum

	sc_signal<sc_logic> x1;

	XORgate* XORa;
	XORgate* XORb;
	AO2gate* AO2a;

	SC_CTOR(oneBitAdder) 
	{
		XORa = new XORgate("xor_insta", sc_time(0.3, SC_NS));
			(*XORa) (i1, i2, x1);
		XORb = new XORgate("xor_instb", sc_time(0.3, SC_NS));
			(*XORb) (x1, i3, o2);
		AO2a = new AO2gate("ao2_insta", sc_time(0.4, SC_NS));
			(*AO2a) (i1, i2, x1, i3, o1);
	}
};

SC_MODULE(Dflipflop)
{
	sc_in<sc_logic> clk, rst, D;
	sc_out<sc_logic> Q;

	SC_CTOR(Dflipflop)
	{
		SC_THREAD(evl);
		sensitive << clk << rst;
	}
	void evl();
};


SC_MODULE(serialAdding)
{
	sc_in<sc_logic> ain, bin, reset, clock;
	sc_out<sc_logic> sum;

	sc_signal<sc_logic> co, ci;

	oneBitAdder* FA1;
	Dflipflop* FF1;

	SC_CTOR(serialAdding)
	{
		FA1 = new oneBitAdder("FA_instance");
			FA1->i1(ain);
			FA1->i2(bin);
			FA1->i3(ci);
			FA1->o1(co);
			FA1->o2(sum);
		FF1 = new Dflipflop("FF_instance");
			FF1->clk(clock);
			FF1->rst(reset);
			FF1->D(co);
			FF1->Q(ci);
	}
};
