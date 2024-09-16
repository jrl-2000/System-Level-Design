#include <systemc.h>

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class memWriterReader : public sc_module {
public:
	tlm_utils::simple_initiator_socket<memWriterReader, 32> memWRSocket;

	SC_CTOR(memWriterReader) : memWRSocket("mem_WR_socket"), nBlockWriteRead(0)
	{
		nBlockWriteRead = new tlm::tlm_generic_payload();
		for (int i = 0; i < 4; i++) *(data+i) = i+192;
		SC_THREAD(nbMemWR);
	}

	tlm::tlm_generic_payload* nBlockWriteRead;
	void nbMemWR();
	void doSomethingGood(tlm::tlm_generic_payload&, sc_time);

	sc_lv<8> data[5];
};
