#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

class memoryUnit : public sc_module {
public:
	tlm_utils::simple_target_socket<memoryUnit> memSocket;

	static const int SIZE = 256;
	int memArray[SIZE];
	const sc_time Latency = sc_time(10, SC_NS);

	SC_CTOR(memoryUnit) : memSocket("memory_side_socket"){
		memSocket.register_b_transport(this, &memoryUnit::b_transport);
		memSocket.register_get_direct_mem_ptr(this, &memoryUnit::get_direct_mem_ptr);

		for (int i = 0; i < SIZE; i++)
			memArray[i] = 0xAA000000 | (rand() % 256);

		SC_THREAD(DMImem);
	}
	virtual void b_transport(tlm::tlm_generic_payload&, sc_time&);
	virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
	void DMImem();
};
