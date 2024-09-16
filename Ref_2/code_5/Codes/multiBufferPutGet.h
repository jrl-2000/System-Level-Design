/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 5: SystemC channels
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "multiBufferChannel.h"

template <int Delay>
SC_MODULE(transmitter) {
	sc_port<put_if<sc_lv<8>>> out;

	SC_CTOR(transmitter) {
		SC_THREAD(putting);
	}
	void putting();
};

template <int Delay>
void transmitter<Delay>::putting() {
	int toTarget;
	sc_lv<8> transmittedData;

	for (int i = 0; i < 36; i++) {
		wait(Delay, SC_NS);
		transmittedData = (sc_lv<8>) i;
		toTarget = rand() % 3; 

		cout << "Transmitter intends to"
			 << " transmit (" << transmittedData << ") at: "
			 << sc_time_stamp() << " to: [" << toTarget << "]\n";

		out->put(toTarget, transmittedData);

		cout << "Transmitter completed transmtting (" 
			 << transmittedData << ") at: "
			 << sc_time_stamp() << " to: [" << toTarget << "]\n";
	}
}


template <int targetNum, int Delay>
SC_MODULE(receiver) {
	sc_port<get_if<sc_lv<8>>> in;
	int Num; 

	SC_CTOR(receiver) {
		SC_THREAD(getting);
	}
	void getting();
};

template <int targetNum, int Delay>
void receiver<targetNum, Delay>::getting() {
	sc_lv<8> receivedData;

	while (1) {
		wait(Delay, SC_NS);

		cout << "Receiver [" << targetNum << "] ready to" << " receive something at: "
			 << sc_time_stamp() << '\n';

		in->get(targetNum, receivedData);

		cout << "Receiver [" << targetNum << "] received (" << receivedData << ") at: "
			 << sc_time_stamp() << " from transmitter\n";
	}
}