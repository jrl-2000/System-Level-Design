#include <systemc.h>
#include "tlm.h"
#include "Bus.h"

SC_MODULE (memoryUnit) {
	sc_export<tlm::tlm_blocking_transport_if<>> memSideBus;
	bus *membus;
	static const int SIZE=256;

	SC_CTOR(memoryUnit) : memSideBus("memorySideBus")
		{
			membus = new bus();
			memSideBus(*membus); // Can go in the TB
			for (int i = 0; i < SIZE; i++)
				memArray[i] = (sc_lv<8>) (i%256 + 192);
	}
public:
	virtual void b_transport( tlm::tlm_generic_payload&, sc_time&);
	sc_lv<8> memArray[SIZE];
};
