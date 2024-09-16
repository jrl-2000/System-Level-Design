#include "memory.h"

memory::memory(sc_module_name NAME, int P, int D) :
		sc_module(NAME), memActivePart(P), memDelay(D) {
	mem = new sc_lv<8>[memActivePart];
	for (int i=0; i< memActivePart; i++) {
		mem[i] = sc_lv<8>(i);
	}
	SC_THREAD(memReadWrite);
}
void memory::memReadWrite() {
	while (1) {
		wait(cs->posedge_event());
		wait(memDelay, SC_NS);
		if (addressBus->read().to_uint() <= memActivePart){
			if (rwbar->read() == SC_LOGIC_1){ // Read operation
				dataBus = *(mem + addressBus->read().to_uint());
				cout << "Reading-" << *(mem + addressBus->read().to_uint())
					<< " from address: ";
			}
			else{
				*(mem + addressBus->read().to_uint()) = dataBus;
				cout << "Writing-" << dataBus << " to address: ";
			}
		}
		memReady->write(SC_LOGIC_1);
		wait(cs->negedge_event());
		dataBus = "ZZZZZZZZ";
		wait(1, SC_NS);
		memReady->write(SC_LOGIC_0);
		cout << addressBus->read().to_uint() << " at:"
			<< sc_time_stamp() << '\n';
	}
}
