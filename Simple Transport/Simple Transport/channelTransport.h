#include "interfaceClasses.h"

class channelTransport : public transport_if 
{
	sc_lv<8> saved;
	sc_event put_event, get_event;
	public:
		channelTransport()  {};
		~channelTransport() {};
		void transport (sc_lv<8> &data);
};