#include "Accelerator.h"

tlm::tlm_sync_enum Accelerator::nb_transport_fw
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
	if (len != 1 || wid != len) {
		receivedTrans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
		return tlm::TLM_COMPLETED;
	}

	if ( cmd == tlm::TLM_READ_COMMAND )
		*(ptr) = *((unsigned char*) (&outReg));
	else if ( cmd == tlm::TLM_WRITE_COMMAND )
		*((unsigned char*)(&inReg + adr)) = *(ptr);

	startCal = ~startCal.read();
	receivedTrans.set_response_status( tlm::TLM_OK_RESPONSE );
	delay = delay + sc_time(50, SC_NS);	
	return tlm::TLM_COMPLETED;
}

void Accelerator::expCalculation(){
	while (true){
		wait(50, SC_NS);
		cout << "The input data: " << (sc_lv<8>)inReg;
		cout <<" was recieved by the accelerator at " << sc_time_stamp() << endl;
		// do some calculations 
		cout << "The accelerator starts the calculations at " << sc_time_stamp() << endl;
		wait((rand() % 200) + 400, SC_NS);

		tlm::tlm_generic_payload* outData = new tlm::tlm_generic_payload;
		tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;	
		if (cmd == tlm::TLM_WRITE_COMMAND) outReg = rand();	
		outData->set_command(cmd);
		outData->set_address(3);		
		outData->set_data_ptr((unsigned char*)&outReg);	
		outData->set_data_length(1);					
		outData->set_streaming_width(1);		
		outData->set_byte_enable_ptr(0);
		outData->set_dmi_allowed(false);
		outData->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

		tlm::tlm_phase backwardPhase = tlm::BEGIN_REQ;
		sc_time delay = sc_time(0, SC_NS); 
		cout << "The accelerator sends the result: " << (sc_lv<8>)outReg;
		cout << " at " << sc_time_stamp() << " delay=" << delay << endl;
		tlm::tlm_sync_enum returnStatus;
		returnStatus = accSocket->nb_transport_bw(*outData, backwardPhase, delay);
		wait(delay);
		if (returnStatus == tlm::TLM_COMPLETED){
			if (outData->is_response_error())
				SC_REPORT_ERROR("TLM-2", "Error in memory handling of b_transport");
			cout << "The accelerator is done and ready for the next execution at " << sc_time_stamp() << endl;
		}
		wait();
	}
}