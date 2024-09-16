#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

class memWriterReader : public sc_module {
public:
	tlm_utils::simple_initiator_socket<memWriterReader> memWRSocket;

	SC_CTOR(memWriterReader) : memWRSocket("mem_WR_socket"), DMIptrValid(false)
  {
		memWRSocket.register_invalidate_direct_mem_ptr(this, &memWriterReader::invalidate_direct_mem_ptr);
		WriteRead = new tlm::tlm_generic_payload;
		
		SC_THREAD(DMImemWR);
  }

  void DMImemWR();
  virtual void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);
  
  tlm::tlm_generic_payload* WriteRead;
  int data;
  bool DMIptrValid;
  tlm::tlm_dmi DMIdata;
};

