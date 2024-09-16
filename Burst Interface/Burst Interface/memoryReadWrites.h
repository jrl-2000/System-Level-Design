#include "busrtInterfaceChannel.h"

// initiator Number, Frequency, Delay
template <int N, int F, int D>
SC_MODULE (initiators) {
	sc_port<requestMem_if<sc_lv<64>, sc_lv<16> >> out;

	SC_CTOR(initiators) {
		SC_THREAD (requesting);
	}
	void requesting();
};

template <int N, int F, int D>
void initiators<N, F, D>::requesting() {
	sc_lv<64> tData; // transmitted Data
	sc_lv<64> dataToWrite; 
	sc_lv<16> tAddress; // transmitted Address (start)
	bool rwbar;

	for (int i = 0; i < 15; i++)
	{
		wait(F, SC_NS);
		rwbar = (bool) (rand() % 2);
		dataToWrite.range(63, 32) = rand();
		dataToWrite.range(31, 0) = rand();

		tData = rwbar ? ((sc_lv<64>)255) : dataToWrite;
		tAddress = ((sc_lv<13>)(rand() % 512), "000"); // From ...000 to ...111

		cout << "\nInitiator {" << N << "} intends to "
			<< (rwbar ? "read from " : "write to ") << "Address:" << tAddress;
		if (!rwbar) cout << " Data:" << tData;
		cout << " at: " << sc_time_stamp() << "\n";
			
		out->requestMem(N, tData, tAddress, rwbar, D);

		cout << "Initiator {" << N << "} completed rwbar:" << rwbar << " Data:" << tData
			<< " Address:" << tAddress << " at: " << sc_time_stamp() << "\n";
	}
}

// memory Number, Frequency, Delay
template <int N, int F, int D>
SC_MODULE(memory) {
	sc_lv<8>* mem; 
	
	sc_port<memRespond_if<sc_lv<8>, sc_lv<16> >> in;

	SC_CTOR(memory) {
		mem = new sc_lv<8>[4096]; // Addressable memory
		for (int i = 0; i < 4096; i++)
			mem[i] = (sc_lv<8>) (i%256); 

		SC_THREAD (responding);
    }
	void responding();
	virtual ~memory(){
		delete[] mem;
	}
};

template <int N, int F, int D>
void memory<N, F, D>::responding() {
	sc_lv<8> rData;    // received Data
	sc_lv<16> rAddress; // received address
	bool rwbar;        // read write
	sc_lv<8> sData;    // sending data back
	int dataInitiator; 

	while (1)
	{
		wait(F, SC_NS);
		in->memForward(dataInitiator, rData, rAddress, rwbar);
			if (rwbar) sData = mem[rAddress.range(11 , 0).to_uint()];
			else mem[rAddress.range(11, 0).to_uint()] = rData;
		in->memBackward(sData, D);
		cout << "Memory " <<(rwbar?"READ":"WROTE") 
			<< " Data:" << (rwbar?sData:rData) << " Address:" << rAddress 
			<< " requested by {"<<dataInitiator<<"}\n";
	}
}
