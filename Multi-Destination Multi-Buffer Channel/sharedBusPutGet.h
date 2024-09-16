#include "sharedBusChannel.h"
#include "receiver.h"
#pragma once

template <int N, int F>
SC_MODULE (transmitter) {
	sc_port<put_if<sc_lv<8>>> out;

	SC_CTOR(transmitter) {
		SC_THREAD (putting);
	}
	void putting();
};

template <int N, int F>
void transmitter<N, F>::putting() {
	int toTarget;
	sc_lv<8> transmittedData;

	for (int i = (N * 16); i<(N * 16 + 15); i++)
	{
		wait(F, SC_NS);
		transmittedData = (sc_lv<8>) i;
		toTarget = rand() % 3;

		cout << "\nMux intends to"
			 << " transmit (" << transmittedData << ") at: "
			 << sc_time_stamp() << " to: [" << toTarget << "]\n";

		out->put(N, toTarget, transmittedData);

	}
}


template <int N, int F>
SC_MODULE(targets) {
	sc_port<get_if<sc_lv<8>>> in;
	sc_port<Buffer_put_if> out;

	SC_CTOR(targets) {
		SC_THREAD (getting);
    }
	void getting();
};

template <int N, int F>
void targets<N, F>::getting() {
	sc_lv<8> receivedData;
	int dataInitiator;


	while (1)
	{
		wait(F, SC_NS); 


		in->get(dataInitiator, N, receivedData);
		cout << "Receiver [" << N << "] received (" << receivedData << ") at: "
			 << sc_time_stamp() << " from: MUX}\n";

		out->Buffer_put(receivedData);
	}
}

