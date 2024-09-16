#include "burstChannel.h"

SC_MODULE (writer) {
	sc_port<burst_write_if> out; // with if out is a pointer

	SC_CTOR (writer)
	{
		SC_THREAD(writeBlocks);
	}
	void writeBlocks();
};

SC_MODULE (reader) {
	sc_port<burst_read_if> in;

	SC_CTOR (reader)
	{
		SC_THREAD(readBlocks);
	}
	void readBlocks();
};

