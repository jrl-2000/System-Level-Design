#include <systemc.h>

template <int T> SC_MODULE (adder){
	sc_in <sc_lv<T> > in1, in2; 
	sc_out < sc_lv<T> > out; 
	
	SC_CTOR (adder)
	{
		SC_METHOD(adding); 
		sensitive << in1 << in2;
	}
	void adding()
	{
		sc_lv<T> vout; 
		vout = (sc_uint<T>) in1 + (sc_uint<T>) in2; 
		out = vout; 
	}
};


