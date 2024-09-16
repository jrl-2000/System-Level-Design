#include "memoryUnit.h"

void memoryUnit::b_transport( tlm::tlm_generic_payload& gotThis, 
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
