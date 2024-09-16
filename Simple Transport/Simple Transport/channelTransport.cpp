#include "channelTransport.h"

void channelTransport::transport(sc_lv<8> &data) {
	if (loading == true) {
		saved = data;
		wait(10, SC_NS);
	}
	else {
		data = saved;
		wait(15, SC_NS);
	}
}
