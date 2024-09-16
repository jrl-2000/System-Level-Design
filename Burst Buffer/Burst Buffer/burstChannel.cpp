#include "burstChannel.h"

void burstBuffer::burstWrite(sc_lv<13> initAddress, sc_lv<64> initData ) {
	sc_lv<16> byteAddress;
	sc_lv<8> byteData;

	burstChannelBusy.lock();

	busRequest->write(SC_LOGIC_1);
	wait(busGrant->posedge_event());

	for (int i = 0; i<8; i++) {
		byteAddress = (initAddress, (sc_lv<3>)i);
		byteData = initData.range(i*8+7, i*8);
		
		memAddress->write(byteAddress);
		memData->write(byteData);
		cs->write(SC_LOGIC_1); 
		rwbar->write(SC_LOGIC_0); 

		wait(memReady->posedge_event());
		cs->write(SC_LOGIC_0);
		wait(memReady->negedge_event());

		memAddress->write("ZZZZZZZZZZZZZZZZ");
		memData->write("ZZZZZZZZ"); 
		cs->write(SC_LOGIC_Z);
		rwbar->write(SC_LOGIC_Z);

		wait(1, SC_NS);
	}
	busRequest->write(SC_LOGIC_0);
	wait(busGrant->negedge_event());
	busRequest->write(SC_LOGIC_Z);

	burstChannelBusy.unlock();
}

void burstBuffer::burstRead(sc_lv<13> initAddress, sc_lv<64>& initData) {
	sc_lv<16> byteAddress;
	sc_lv<8> byteData;

	burstChannelBusy.lock();

	busRequest->write(SC_LOGIC_1);
	wait(busGrant->posedge_event());
	for (int i = 0; i<8; i++) {
		byteAddress = (initAddress, (sc_lv<3>)i);
		memAddress->write(byteAddress);
		cs->write(SC_LOGIC_1);
		rwbar->write(SC_LOGIC_1);
		wait(memReady->posedge_event());
		byteData = memData->read();
		initData.range(i * 8 + 7, i * 8) = byteData;

		cs->write(SC_LOGIC_0); 
		wait(memReady->negedge_event());

		memAddress->write("ZZZZZZZZZZZZZZZZ");
		memData->write("ZZZZZZZZ");
		cs->write(SC_LOGIC_Z);
		rwbar->write(SC_LOGIC_Z);

		wait(1, SC_NS);
	}
	busRequest->write(SC_LOGIC_0);
	wait(busGrant->negedge_event());
	busRequest->write(SC_LOGIC_Z);

	burstChannelBusy.unlock();
}