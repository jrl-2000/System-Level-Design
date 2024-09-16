#include <systemc.h>
#include "tlm.h"

class bus : public tlm::tlm_blocking_transport_if<>
{
public:
	bus() {};
	~bus() {};

	virtual void b_transport(tlm::tlm_generic_payload&, sc_time&){};
};

