#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

class Accelerator : public sc_module {
public:
	tlm_utils::simple_target_socket<Accelerator, 32> accSocket;
	
	SC_CTOR(Accelerator) : accSocket("Accelerator_socket") {
		
		startCal = SC_LOGIC_0;

		accSocket.register_nb_transport_fw(this, &Accelerator::nb_transport_fw);
		SC_THREAD(expCalculation);
		sensitive << startCal;
	}

	virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload&,
		                                        tlm::tlm_phase&, sc_time& );
	void expCalculation();
	int inReg;
	int outReg;
	sc_signal <sc_logic> startCal;
};

