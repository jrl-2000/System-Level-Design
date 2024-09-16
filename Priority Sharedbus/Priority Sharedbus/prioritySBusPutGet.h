#include "prioritySBusChannel.h"

// initiator Number, Frequency, Delay
template <int N, int F, int D>
SC_MODULE (initiators) {
	sc_port<put_if<sc_lv<8>>> out;

	SC_CTOR(initiators) {
		SC_THREAD (putting);
	}
	void putting();
};

template <int N, int F, int D>
void initiators<N, F, D>::putting() {
	int toTarget;
	sc_lv<8> tData; // transmitted Data

	for (int i = (N * 16); i<(N * 16 + 15); i++)
	{
		wait(F, SC_NS);
		tData = (sc_lv<8>) (rand() % 256);
		toTarget = 0;

		cout << "\nInitiator {" << N << "} intends to"
			<< " transmit (" << tData << ") at: "
			<< sc_time_stamp() << " to: [" << toTarget << "]\n";

		out->put(N, toTarget, tData, D);
		cout << "Initiator {" << N << "} completed transmtting (" << tData << ") at: "
			<< sc_time_stamp() << " to: [" << toTarget << "]\n";
	}
}

// target Number, Frequency, Delay
template <int N, int F, int D>
SC_MODULE(targets) {
	sc_port<get_if<sc_lv<8>>> in;

	SC_CTOR(targets) {
		SC_THREAD (getting);
    }
	void getting();
};

template <int N, int F, int D>
void targets<N, F, D>::getting() {
	sc_lv<8> rData; // received Data
	int dataInitiator; 

	while (1)
	{
		wait(F, SC_NS);

		cout << "Target [" << N << "] ready to" << " receive something at: "
			<< sc_time_stamp() << '\n';

		in->get(dataInitiator, N, rData, D);
		cout << "Target [" << N << "] received (" << rData << ") at: "
			 << sc_time_stamp() << " from: {" << dataInitiator << "}\n";
	}
}
