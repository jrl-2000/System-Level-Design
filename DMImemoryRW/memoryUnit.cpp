#include "memoryUnit.h"


void memoryUnit::b_transport(tlm::tlm_generic_payload& gotThis, sc_time& delayValue)
{
	tlm::tlm_command cmd = gotThis.get_command();
	uint64			 adr = gotThis.get_address()/4;
	unsigned char*   ptr = gotThis.get_data_ptr();
	unsigned int     len = gotThis.get_data_length();
	unsigned char*   byt = gotThis.get_byte_enable_ptr();
	unsigned int     wid = gotThis.get_streaming_width();

	if (adr >= uint64(SIZE) || byt != 0 || len > 4 || wid < len)
		SC_REPORT_ERROR("TLM-2.0: ", "Inconsistant Generic Payload");

	unsigned int i;
	if (cmd == tlm::TLM_READ_COMMAND){
		memcpy(ptr, &memArray[adr], len);
	}
	else if (cmd == tlm::TLM_WRITE_COMMAND){
		memcpy(&memArray[adr], ptr, len);
	}
	wait(delayValue);
	gotThis.set_dmi_allowed(true);
	gotThis.set_response_status(tlm::TLM_OK_RESPONSE);
}

bool memoryUnit::get_direct_mem_ptr(tlm::tlm_generic_payload& gotThis, tlm::tlm_dmi& dmi_data)
{
    dmi_data.allow_read_write();

	dmi_data.set_dmi_ptr((unsigned char*)&memArray[0]);
    dmi_data.set_start_address( 0 );
    dmi_data.set_end_address( SIZE*4-1 );
	dmi_data.set_read_latency(Latency);
	dmi_data.set_write_latency(Latency);

    return true;
}

void memoryUnit::DMImem()
{
    for (int i = 0; i < 4; i++) {
		wait(Latency * 8);
		memSocket->invalidate_direct_mem_ptr(0, SIZE - 1);
    } 
}
