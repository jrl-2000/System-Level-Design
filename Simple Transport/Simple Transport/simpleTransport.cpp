#include "simpleTransport.h"

void transmitter::transportingOut() {
	int i;
	sc_lv<8> dataToPut;
	out->loading = false;
	for (i=0; i<27; i++)
	{
		dataToPut = (sc_lv<8>) i;
		out->loading = true;
		out->transport(dataToPut);
		out->INCOMPLETE.notify();
		cout << "Data: (" << dataToPut << ") was transmitted at: "
			<< sc_time_stamp() << '\n';
		wait(out->COMPLETE);
	}
}

void receiver::transportingIn() {
	sc_lv<8> dataThatGot;
	int i; for (i=0; i<27; i++)
	while (1) 
	{
		wait(in->INCOMPLETE);
		in->loading = false;
		in->transport(dataThatGot);
		in->COMPLETE.notify();
		cout << "Data: (" << dataThatGot << ") was received at: "
			<< sc_time_stamp() << '\n';
	}
}

