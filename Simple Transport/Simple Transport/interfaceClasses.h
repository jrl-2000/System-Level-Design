#include <systemc.h>

class transport_if : virtual public sc_interface
{
	public:
		bool loading;
		sc_event INCOMPLETE;
		sc_event COMPLETE;
		virtual void transport(sc_lv<8> &) = 0;
};
