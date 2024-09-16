#include <systemc.h>

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class memoryUnit : public sc_module {
public:
	tlm_utils::simple_target_socket<memoryUnit, 32> memSocket;

	static const int SIZE=256;

	SC_CTOR(memoryUnit) : memSocket("memory_side_socket") {
		memSocket.register_nb_transport_fw(this, &memoryUnit::nb_transport_fw);

		// Initialize memory
		for (int i = 0; i < SIZE; i++)
			memArray[i] = (sc_lv<8>) (i%256 + 192);
	}

	virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload&,
		                                        tlm::tlm_phase&, sc_time& );
	sc_lv<8> memArray[SIZE];
};
