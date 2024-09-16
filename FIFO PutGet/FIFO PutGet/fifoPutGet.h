#include "fifoChannel.h"

SC_MODULE (transmitter) {
	sc_port<put_if<sc_lv<8>>> out;

	SC_CTOR(transmitter) {
		SC_THREAD (putting);
	}
	void putting();
};

SC_MODULE (receiver) {
	sc_port<get_if<sc_lv<8>>> in;

	SC_CTOR(receiver) {
		SC_THREAD (getting);
    }
	void getting();
};

