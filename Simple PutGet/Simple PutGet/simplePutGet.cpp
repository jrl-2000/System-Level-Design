#include "simplePutGet.h"

void transmitter::putting() {
	int i;
	sc_lv<8> dataToPut;
	for (i=0; i<27; i++)
	{
		wait(7, SC_NS);
		dataToPut = (sc_lv<8>) i;
		out->put(dataToPut); 
		cout << "Data: (" << dataToPut << ") was transmitted at: " 
			 << sc_time_stamp() << '\n';
	}
}

void receiver::getting() {
	sc_lv<8> dataThatGot;
	int i; for (i=0; i<27; i++)
	while (1) 
	{
		wait(3, SC_NS);
		in->get(dataThatGot);
		cout << "Data: (" << dataThatGot << ") was received at: " 
			 << sc_time_stamp() << '\n';
	}
}
