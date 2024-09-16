#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

class Processor : public sc_module {
public:
	tlm_utils::simple_initiator_socket<Processor, 32> procSocket;  

	SC_CTOR(Processor) : procSocket("Processor_Socket"), inData(0)
	{
		inData = new tlm::tlm_generic_payload();
		SC_THREAD(exeInstructions);
		procSocket.register_nb_transport_bw(this, &Processor::nb_transport_bw);		
	}
	tlm::tlm_generic_payload* inData;
	void exeInstructions();
	virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_time&);
	int data;
	int result;
};

