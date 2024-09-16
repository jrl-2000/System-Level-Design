
#pragma once
#include "BufferPutGet.h"

SC_MODULE(BufferPutGet_TB) {
	multiBufferChannel<sc_lv<8>, 3>* Channel;
	transmitter<0, 9, 0>* INI0;
	receiver<0, 12, 0>* RCV0; 
	



	SC_CTOR(BufferPutGet_TB) {
		Channel = new multiBufferChannel<sc_lv<8>, 3>;
		
		INI0 = new transmitter<0, 9, 0>("Transmitter");
		INI0->out(*Channel);
		
		RCV0 = new receiver<0, 12, 0>("Receiver0");
		RCV0->in(*Channel); 

		/*
		RCV1 = new receiver<1, 5>("Receiver1");
		RCV1->in(*Channel);
		RCV2 = new receiver<2, 9>("Receiver2");
		RCV2->in(*Channel);
		*/
	}
};