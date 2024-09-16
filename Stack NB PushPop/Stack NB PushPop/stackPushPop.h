#include "stackChannel.h"

SC_MODULE (transmitter) {
	sc_port<stack_push_if> out; // with if out is a pointer

	SC_CTOR (transmitter)
	{
		SC_THREAD(pushSome);
	}
	void pushSome();
};

SC_MODULE (receiver) {
	sc_port<stack_pop_if> in;

	SC_CTOR (receiver)
	{
		SC_THREAD(popThem);
	}
	void popThem();
};

