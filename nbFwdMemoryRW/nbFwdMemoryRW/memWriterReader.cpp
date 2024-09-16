#include "memWriterReader.h"

void memWriterReader::nbMemWR()
{
	tlm::tlm_phase forwardPhase;
	sc_time processTime; // Processing time of initiator prior to call

	processTime = sc_time(0, SC_PS);
	for (int i = 0; i < 111; i = i + 11){
		tlm::tlm_command cmd = (tlm::tlm_command)(rand() % 2);
		if (cmd == tlm::TLM_WRITE_COMMAND) {
			data[0] = (sc_lv<8>) (i+5);
			data[1] = (sc_lv<8>) (i+6);
			data[2] = (sc_lv<8>) (i+7);
			data[3] = (sc_lv<8>) (i+8);
			data[4] = (sc_lv<8>) (i+9);
		}

		nBlockWriteRead->set_command( cmd );
		nBlockWriteRead->set_address( i );
		nBlockWriteRead->set_data_ptr( (unsigned char*) data );
		nBlockWriteRead->set_data_length( 5 );
		nBlockWriteRead->set_streaming_width( 5 );
		nBlockWriteRead->set_byte_enable_ptr( 0 );
		nBlockWriteRead->set_dmi_allowed( false );
		nBlockWriteRead->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		forwardPhase = tlm::BEGIN_REQ;

		cout << (cmd ? 'W' : 'R') << ", @" << i << " data:";
		sc_lv<8> vv;
		for(int j=0; j<5; j++) {vv=data[j]; cout << vv << " ";}
		cout << " @time " << sc_time_stamp() <<" delay=" << processTime << '\n';

		tlm::tlm_sync_enum returnStatus;
		returnStatus = memWRSocket->
			nb_transport_fw(*nBlockWriteRead, forwardPhase, processTime);

		if (returnStatus == tlm::TLM_COMPLETED) 
			doSomethingGood( *nBlockWriteRead, processTime );
	}
}

void memWriterReader::doSomethingGood( tlm::tlm_generic_payload& completeTrans, 
	                                   sc_time totalTime )
{
	if ( completeTrans.is_response_error() )
		SC_REPORT_ERROR("TLM-2", "error...\n");

	tlm::tlm_command cmd = completeTrans.get_command();
	uint64           adr = completeTrans.get_address();
	int*             ptr = reinterpret_cast<int*>( completeTrans.get_data_ptr() );

	cout << "Above was completed @time " << totalTime << '\n';
}
