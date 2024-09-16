#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

// Target 1
// Interconnect
SC_MODULE (Interconnect) {
	tlm_utils::simple_target_socket<Interconnect> memSideSocket1;
	tlm_utils::simple_initiator_socket<Interconnect> memWriterReaderSocket1;

	static const int SIZE=256;

	void memWritingReading1();
	tlm::tlm_generic_payload* blockWriteRead;

	SC_CTOR(Interconnect) : memSideSocket1("Interconnect")
		{
			memSideSocket1.register_b_transport(this, &Interconnect::b_transport);

			for (int i = 0; i < SIZE; i++)
				memArray[i] = (sc_lv<8>) (i%256 + 192);
	}

public:
	virtual void b_transport( tlm::tlm_generic_payload&, sc_time&);
	sc_lv<8> memArray[SIZE];
	sc_lv<8> data[5];
};



SC_MODULE(memoryArray) {
	tlm_utils::simple_target_socket<memoryArray> memSideSocket;

	static const int SIZE = 256;

	SC_CTOR(memoryArray) : memSideSocket("memorySideSocket")
	{
		memSideSocket.register_b_transport(this, &memoryArray::b_transport);

		for (int i = 0; i < SIZE; i++)
			memArray[i] = (sc_lv<8>) (i % 256 + 192);
	}

public:
	virtual void b_transport(tlm::tlm_generic_payload&, sc_time&);
	sc_lv<8> memArray[SIZE];
};
