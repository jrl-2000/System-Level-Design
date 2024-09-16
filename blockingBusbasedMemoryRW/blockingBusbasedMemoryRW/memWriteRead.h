#include <systemc.h>
#include "tlm.h"

class memWriterReader : public sc_module {
public:
	sc_port<tlm::tlm_blocking_transport_if<>> memWriterReaderBus;
	
	SC_CTOR(memWriterReader) :blockWriteRead(0) {
		blockWriteRead = new tlm::tlm_generic_payload;

		for (int i = 0; i < 4; i++) *(data+i) = i+192;

		SC_THREAD(memWritingReading);
		}
	
	void memWritingReading();
	tlm::tlm_generic_payload* blockWriteRead; 

	sc_lv<8> data[5];
};
