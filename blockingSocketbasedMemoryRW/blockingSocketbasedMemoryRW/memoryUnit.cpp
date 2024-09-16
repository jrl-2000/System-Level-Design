#include "memoryUnit.h"

void Interconnect::b_transport( tlm::tlm_generic_payload& gotThis,
	                          sc_time& delayValue )
	{
		tlm::tlm_command cmd = gotThis.get_command();
		uint64			 adr = gotThis.get_address();
		unsigned char*   ptr = gotThis.get_data_ptr();
		unsigned int     len = gotThis.get_data_length();
		unsigned char*   byt = gotThis.get_byte_enable_ptr();
		unsigned int     wid = gotThis.get_streaming_width();

 		if (adr >= uint64(SIZE) || byt != 0 || len > 5 || wid < len)
			SC_REPORT_ERROR("TLM-2.0: ","Inconsistant Generic Payload");

		unsigned int i;

		if ( cmd == tlm::TLM_READ_COMMAND ){
			for(i=0; i<len; i=i+1) { 
				*(ptr+i) = *((unsigned char*) (memArray+adr+i));
			}			
		}
		else if ( cmd == tlm::TLM_WRITE_COMMAND ){
			for(i=0; i<len; i=i+1) {
				*((unsigned char*) (memArray+adr+i)) = *(ptr+i);
			}
		}

 		gotThis.set_response_status( tlm::TLM_OK_RESPONSE );
		wait(delayValue);
}

void memoryArray::b_transport(tlm::tlm_generic_payload& gotThis,
	sc_time& delayValue)
{
	tlm::tlm_command cmd = gotThis.get_command();
	uint64			 adr = gotThis.get_address();
	unsigned char* ptr = gotThis.get_data_ptr();
	unsigned int     len = gotThis.get_data_length();
	unsigned char* byt = gotThis.get_byte_enable_ptr();
	unsigned int     wid = gotThis.get_streaming_width();

	if (adr >= uint64(SIZE) || byt != 0 || len > 5 || wid < len)
		SC_REPORT_ERROR("TLM-2.0: ", "Inconsistant Generic Payload");

	unsigned int i;

	if (cmd == tlm::TLM_READ_COMMAND) {
		for (i = 0; i < len; i = i + 1) {
			*(ptr + i) = *((unsigned char*)(memArray + adr + i));
		}
	}
	else if (cmd == tlm::TLM_WRITE_COMMAND) {
		for (i = 0; i < len; i = i + 1) {
			*((unsigned char*)(memArray + adr + i)) = *(ptr + i);
		}
	}

	gotThis.set_response_status(tlm::TLM_OK_RESPONSE);
	wait(delayValue);
}

void Interconnect::memWritingReading1() {
	sc_time blockedTime = sc_time(13, SC_NS);
	sc_time pauseTime = sc_time(15, SC_NS);

	for (int i = 0; i < 111; i += 11) {
		tlm::tlm_command cmd = (tlm::tlm_command)(rand() % 2);
		if (cmd == tlm::TLM_WRITE_COMMAND) {
			data[0] = (sc_lv<8>) (i + 5);
			data[1] = (sc_lv<8>) (i + 6);
			data[2] = (sc_lv<8>) (i + 7);
			data[3] = (sc_lv<8>) (i + 8);
			data[4] = (sc_lv<8>) (i + 9);
		}

		blockWriteRead->set_command(cmd);
		blockWriteRead->set_address(i);
		blockWriteRead->set_data_ptr((unsigned char*)data); 
		blockWriteRead->set_data_length(5);
		blockWriteRead->set_streaming_width(5);
		blockWriteRead->set_byte_enable_ptr(0);
		blockWriteRead->set_dmi_allowed(false);
		blockWriteRead->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

		memWriterReaderSocket1->b_transport(*blockWriteRead, blockedTime);


		if (blockWriteRead->is_response_error())
			SC_REPORT_ERROR("TLM-2", "Error in memory handling of b_transport");

		cout << " At time: " << sc_time_stamp() << "WR: "
			<< (cmd ? 'W' : 'R') << ", Iteration:" << i << " data:";
		sc_lv<8> vv;
		for (int j = 0; j < 5; j++) { vv = data[j]; cout << vv << " "; } cout << '\n';
		// wait(pauseTime);
	}
}



