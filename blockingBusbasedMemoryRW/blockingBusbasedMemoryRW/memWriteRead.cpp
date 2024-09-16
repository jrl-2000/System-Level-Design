#include "memWriteRead.h"

void memWriterReader::memWritingReading(){		
	sc_time blockedTime = sc_time(13, SC_NS);
	sc_time pauseTime = sc_time(15, SC_NS);

	for (int i = 0; i < 111; i += 11) {
		tlm::tlm_command cmd = (tlm::tlm_command)(rand() % 2);
		if (cmd == tlm::TLM_WRITE_COMMAND) {
			data[0] = (sc_lv<8>) (i+5);
			data[1] = (sc_lv<8>) (i+6);
			data[2] = (sc_lv<8>) (i+7);
			data[3] = (sc_lv<8>) (i+8);
			data[4] = (sc_lv<8>) (i+9);
		}
		
		blockWriteRead->set_command( cmd );
		blockWriteRead->set_address( i );
		blockWriteRead->set_data_ptr( (unsigned char*) data );
		blockWriteRead->set_data_length( 5 );     
		blockWriteRead->set_streaming_width( 5 ); 
		blockWriteRead->set_byte_enable_ptr( 0 ); 
		blockWriteRead->set_dmi_allowed( false ); 
		blockWriteRead->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

		memWriterReaderBus->b_transport( *blockWriteRead, blockedTime ); 

		cout << "WR: " << (cmd ? 'W' : 'R') << ", @" << i << " data:";
		sc_lv<8> vv; 
		for(int j=0; j<5; j++) {vv=data[j]; cout << vv << " ";} cout << '\n'; 

		wait(pauseTime);
	}
}
