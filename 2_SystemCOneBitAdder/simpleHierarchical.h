#include <systemc.h>

SC_MODULE(XORgate)
{
	sc_in<sc_logic> i1, i2;
	sc_out<sc_logic> o1;

	SC_CTOR(XORgate)
	{
		SC_METHOD(evl);
		sensitive << i1 << i2;
	}
	void evl();
};

SC_MODULE(AO2gate)
{
	sc_in<sc_logic> i1, i2, i3, i4;
	sc_out<sc_logic> o1;

	SC_CTOR(AO2gate)
	{
		SC_METHOD(evl);
		sensitive << i1 << i2 << i3 << i4;
	}
	void evl();
};

SC_MODULE(oneBitAdder)
{
	sc_in<sc_logic> i1, i2, i3;
	sc_out<sc_logic> o1, o2;

	sc_signal<sc_logic> x1;

	XORgate* XORa;
	XORgate* XORb;
	AO2gate* AO2a;

	SC_CTOR(oneBitAdder) 
	{
		XORa = new XORgate("xor_insta");
			(*XORa) (i1, i2, x1);
		XORb = new XORgate("xor_instb");
			(*XORb) (x1, i3, o2);
		AO2a = new AO2gate("ao2_insta");
			(*AO2a) (i1, i2, x1, i3, o1);
	}
};
