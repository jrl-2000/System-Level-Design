#include "sharedBusPutGet.h"
#pragma once


SC_MODULE (sharedBusPutGet_TB) {
	
	sharedBus<sc_lv<8>, 1, 3> * MULTI_DEST_MULTI_BUFF_CH_MUX;

	transmitter<1, 3>* TRAN0;

	targets<0, 7>* TARG0;
	targets<1, 4>* TARG1;
	targets<2, 4>* TARG2;

	buffer<1>* BUFF0;
	buffer<1>* BUFF1;
	buffer<1>* BUFF2;

	receiver<1>* RCVR0;
	receiver<1>* RCVR1;
	receiver<1>* RCVR2;

	
	SC_CTOR(sharedBusPutGet_TB) {
		MULTI_DEST_MULTI_BUFF_CH_MUX = new sharedBus<sc_lv<8>, 1, 3>;

		TRAN0 = new transmitter<1, 3>("Transmitter");
		TRAN0->out(*MULTI_DEST_MULTI_BUFF_CH_MUX);


		BUFF0 = new buffer<1>();
		BUFF1 = new buffer<1>();
		BUFF2 = new buffer<1>();

		TARG0 = new targets<0, 7>("Target0");
		TARG0->in(*MULTI_DEST_MULTI_BUFF_CH_MUX);
		TARG0->out(*BUFF0);
		TARG1 = new targets<1, 4>("Target1");
		TARG1->in(*MULTI_DEST_MULTI_BUFF_CH_MUX);
		TARG1->out(*BUFF1);
		TARG2 = new targets<2, 4>("Target2");
		TARG2->in(*MULTI_DEST_MULTI_BUFF_CH_MUX);
		TARG2->out(*BUFF2);
	

		RCVR0 = new receiver<1>("Receiver0");
		RCVR0->in(*BUFF0);
		RCVR1 = new receiver<1>("Receiver1");
		RCVR1->in(*BUFF1);
		RCVR2 = new receiver<1>("Receiver2");
		RCVR2->in(*BUFF2);

	}
};

