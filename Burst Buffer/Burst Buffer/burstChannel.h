#include "interfaceClasses.h"

class burstBuffer : public sc_channel, public burst_write_if, public burst_read_if {

public:
	sc_out_rv<16> memAddress;
	sc_inout_rv<8> memData;
	sc_out_resolved rwbar, cs;
	sc_in_resolved memReady;
	sc_out_resolved busRequest;
	sc_in<sc_logic> busGrant;

	sc_mutex burstChannelBusy;

	burstBuffer (sc_module_name NAME): sc_channel(NAME){};
//	~burstBuffer(){};

	virtual void burstWrite(sc_lv<13> initAddress, sc_lv<64> initData);
	virtual void burstRead(sc_lv<13> initAddress, sc_lv<64>& initData);
};
