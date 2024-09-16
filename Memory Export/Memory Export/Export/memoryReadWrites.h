#include "memoryAccessChannel.h"

// initiator Number, Frequency, Delay
template <int N, int F, int D>
SC_MODULE (initiators) {
	sc_port<requestMem_if<sc_lv<8>>> out;

	SC_CTOR(initiators) {
		SC_THREAD (requesting);
	}
	void requesting();
};

template <int N, int F, int D>
void initiators<N, F, D>::requesting() {
	sc_lv<8> tData; // transmitted Data
	sc_lv<8> tAddress; // transmitted Address
	bool rwbar;

	for (int i = (N * 16); i<(N * 16 + 15); i++)
	{
		wait(F, SC_NS);
		rwbar = (bool) (rand() % 2);
		tData = (rwbar?((sc_lv<8>)255) : (sc_lv<8>) (rand() % 256));
		tAddress = (sc_lv<8>) (rand() % 256);

		cout << "\nInitiator {" << N << "} intends to "
			<< (rwbar ? "read from " : "write to ") << "address: " << tAddress;
		if (!rwbar) cout << " Data: " << tData;
		cout << " at: " << sc_time_stamp() << "\n";
			
		out->requestMem(N, tData, tAddress, rwbar, D);

		cout << "Back to Initiator: rwbar:" << rwbar << " datafield:" << tData
			<< " addressfield:" << tAddress << '\n';


		cout << "Initiator {" << N << "} completed ";
		if (rwbar) cout << "reading data: " << tData; else cout << "writing";
		cout << " at: " << sc_time_stamp() << "\n";
	}
}

// memory Number, Frequency, Delay
template <int N, int F, int D>
SC_MODULE(memory) {
	sc_export<memRespond_if<sc_lv<8>>> in;
	sc_lv<8> mem[256];
	memoryAccess<sc_lv<8>, 4> * memBus;

	SC_CTOR(memory) {
		memBus = new memoryAccess<sc_lv<8>, 4>;
		SC_THREAD (responding);
    }
	void responding();
};

template <int N, int F, int D>
void memory<N, F, D>::responding() {
	sc_lv<8> rData; // received Data
	int dataInitiator; 

	while (1)
	{
		//cout << "target> " << N <<" "<< F <<" "<< D <<" "<< '\n';	
		wait(F, SC_NS);
		//cout << "target< " << N <<" "<< F <<" "<< D <<" "<< '\n';

		//cout << "Memory [" << N << "] ready to" << " do something at: "
		//	<< sc_time_stamp() << '\n';

		in->memRespond(dataInitiator, D);
		//cout << "Memory [" << N << "] did something (" << rData << ") at: "
		//	 << sc_time_stamp() << " requested by: {" << dataInitiator << "}\n";
	}
}
