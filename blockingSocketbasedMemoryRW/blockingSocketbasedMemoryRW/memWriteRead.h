#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"


// Initiator
class memWriterReader : public sc_module {
public:
	tlm_utils::simple_initiator_socket<memWriterReader> memWriterReaderSocket;
	
	SC_CTOR(memWriterReader) : memWriterReaderSocket("Writer-Socket"), blockWriteRead(0) {
		blockWriteRead = new tlm::tlm_generic_payload;

		for (int i = 0; i < 4; i++) *(data+i) = i+192;

		SC_THREAD(memWritingReading);
		}
	
	void memWritingReading();
	tlm::tlm_generic_payload* blockWriteRead; 

	sc_lv<8> data[5];
};
