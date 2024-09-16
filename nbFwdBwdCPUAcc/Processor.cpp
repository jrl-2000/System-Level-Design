#include "Processor.h"

void Processor::exeInstructions(){
	tlm::tlm_phase forwardPhase;
	sc_time delay; 	

	for (int i = 64; i < 104; i = i + 8){
		cout << "*************************************************************" << endl;
		tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;	
		if (cmd == tlm::TLM_WRITE_COMMAND)	data = i;

		inData->set_command( cmd );
		inData->set_address( 0 );	
		inData->set_data_ptr( (unsigned char*) &data );	
		inData->set_data_length( 1 );					
		inData->set_streaming_width( 1 );				
		inData->set_byte_enable_ptr( 0 );
		inData->set_dmi_allowed( false );
		inData->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		forwardPhase = tlm::BEGIN_REQ;
		delay = sc_time(0, SC_NS);
		cout << "The CPU sends an input data: " << (sc_lv<8>)data;
		cout << " at " << sc_time_stamp() << " delay=" << delay << '\n';
		tlm::tlm_sync_enum returnStatus;
		returnStatus = procSocket->nb_transport_fw(*inData, forwardPhase, delay);
		wait(delay);
		if (returnStatus == tlm::TLM_COMPLETED){
			if (inData->is_response_error())
				SC_REPORT_ERROR("TLM-2", "Error in memory handling of b_transport");
			cout << "The CPU is done with communication at " << sc_time_stamp() << endl;
		}
		cout << "The CPU is processing some instruction at " << sc_time_stamp() << '\n';
		wait(1300, SC_NS);
	}
}


tlm::tlm_sync_enum Processor::nb_transport_bw(tlm::tlm_generic_payload& receivedTrans,
	tlm::tlm_phase& phase, sc_time& delay){
	tlm::tlm_command cmd = receivedTrans.get_command();
	uint64           adr = receivedTrans.get_address();
	unsigned char*   ptr = receivedTrans.get_data_ptr();
	unsigned int     len = receivedTrans.get_data_length();
	unsigned char*   byt = receivedTrans.get_byte_enable_ptr();
	unsigned int     wid = receivedTrans.get_streaming_width();

	if (byt != 0) {
		receivedTrans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
		return tlm::TLM_COMPLETED;
	}
	if (len != 1 || wid != len) {
		receivedTrans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
		return tlm::TLM_COMPLETED;
	}

	if (cmd == tlm::TLM_READ_COMMAND)
			*(ptr) = *((unsigned char*)(&data + adr));

	else if (cmd == tlm::TLM_WRITE_COMMAND)
			*((unsigned char*)(&result + adr)) = *(ptr);

	receivedTrans.set_response_status(tlm::TLM_OK_RESPONSE);
	delay = delay + sc_time(57, SC_NS);
	cout << "The result data: " << (sc_lv<8>)(*((unsigned char*)(&result + adr)));
	cout << " was recieved by the CPU at " << sc_time_stamp() << endl;
	return tlm::TLM_COMPLETED;
}