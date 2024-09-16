#include "memoryUnit.h"

tlm::tlm_sync_enum memoryUnit::nb_transport_fw
       (tlm::tlm_generic_payload& receivedTrans,
        tlm::tlm_phase& phase, sc_time& delay ){

	tlm::tlm_command cmd = receivedTrans.get_command();
	uint64           adr = receivedTrans.get_address();
	unsigned char*   ptr = receivedTrans.get_data_ptr();
	unsigned int     len = receivedTrans.get_data_length();
	unsigned char*   byt = receivedTrans.get_byte_enable_ptr();
	unsigned int     wid = receivedTrans.get_streaming_width();

	if (byt != 0) {
		receivedTrans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
		return tlm::TLM_COMPLETED;
	}
	if (len > 5 || wid < len) {
		receivedTrans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
		return tlm::TLM_COMPLETED;
	}
	unsigned int i;
	if ( cmd == tlm::TLM_READ_COMMAND )
		for(i=0; i<len; i=i+1) {
			*(ptr+i) = *((unsigned char*) (memArray+adr+i));
		}
	else if ( cmd == tlm::TLM_WRITE_COMMAND )
		for(i=0; i<len; i=i+1) {
			*((unsigned char*) (memArray+adr+i)) = *(ptr+i);
		}

	receivedTrans.set_response_status( tlm::TLM_OK_RESPONSE );
	delay = delay + sc_time(123, SC_NS);
	return tlm::TLM_COMPLETED;
}
