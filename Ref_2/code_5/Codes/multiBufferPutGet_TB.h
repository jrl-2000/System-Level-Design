/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 5: SystemC channels
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "multiBufferPutGet.h"

SC_MODULE(multiBufferPutGet_TB) {
	multiBufferChannel<sc_lv<8>, 3>* Channel;
	transmitter<7>* TRS; 
	receiver<0, 12>* RCV0; 
	receiver<1, 5>* RCV1;
	receiver<2, 9>* RCV2; 


	SC_CTOR(multiBufferPutGet_TB) {
		Channel = new multiBufferChannel<sc_lv<8>, 3>;
		
		TRS = new transmitter<7>("Transmitter");
		TRS->out(*Channel);
		
		RCV0 = new receiver<0, 12>("Receiver0");
		RCV0->in(*Channel); 
		RCV1 = new receiver<1, 5>("Receiver1");
		RCV1->in(*Channel);
		RCV2 = new receiver<2, 9>("Receiver2");
		RCV2->in(*Channel);
	}
};