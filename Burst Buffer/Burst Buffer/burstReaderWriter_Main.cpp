#include "burstReaderWriter_TB.h"
int sc_main (int argc , char *argv[]) {
   burstReaderWriter_TB SPP1("burstReaderWriter");

   sc_trace_file *wf = sc_create_vcd_trace_file("burstReaderWriter");
   // Dump memory signals
   sc_trace(wf, SPP1.req0, "Request");
   sc_trace(wf, SPP1.gnt0, "Grant");
   sc_trace(wf, SPP1.memCs, "CS");
   sc_trace(wf, SPP1.memRwbar, "RWbar");
   sc_trace(wf, SPP1.memAddressBus, "Address");
   sc_trace(wf, SPP1.memDataBus, "Data");
   sc_trace(wf, SPP1.memReady, "memReady");

   sc_start();// 6200, SC_NS);
   sc_close_vcd_trace_file(wf);
   return 0;
}

