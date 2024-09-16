#include "burstReaderWriter.h"
#include "memory.h"
#include "arbiter.h"

SC_MODULE(burstReaderWriter_TB) {
	sc_signal_rv<16> memAddressBus;
	sc_signal_rv<8> memDataBus;
	sc_signal_resolved memRwbar, memCs;
	sc_signal_resolved memReady;
	sc_signal<sc_lv<4>> req;
	sc_signal<sc_lv<4>> gnt;
	sc_signal_resolved req0;
	sc_signal<sc_logic> gnt0;

	burstBuffer* BBChannel;
	writer* WR1;
	reader* RD1;
	memory* MEM1;
	arbiter* ARB1;

	SC_CTOR(burstReaderWriter_TB){
		BBChannel = new burstBuffer("burstBufferChannel");
			BBChannel->memAddress(memAddressBus);
			BBChannel->memData(memDataBus);
			BBChannel->rwbar(memRwbar);
			BBChannel->cs(memCs);
			BBChannel->memReady(memReady);
			BBChannel->busRequest(req0);
			BBChannel->busGrant(gnt0);

		WR1 = new writer("Writer");
			WR1->out(*BBChannel);
		RD1 = new reader("Reader");
			RD1->in(*BBChannel);
		MEM1 = new memory("Memory",1024, 5);
			MEM1->addressBus(memAddressBus);
			MEM1->dataBus(memDataBus);
			MEM1->rwbar(memRwbar);
			MEM1->cs(memCs);
			MEM1->memReady(memReady);
		ARB1 = new arbiter("Arbiter", 1);
			ARB1->request(req);
			ARB1->grant(gnt);
		SC_METHOD(setRequest);
			sensitive << req0;
		SC_METHOD(setGrant);
			sensitive << gnt;
	}
	void setRequest(){ sc_lv<4> r; r = 0; r[0] = req0; req.write(r); }
	void setGrant(){gnt0 = gnt.read()[0]; }
};

