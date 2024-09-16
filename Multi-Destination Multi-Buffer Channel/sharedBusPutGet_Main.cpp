#include "sharedBusPutGet_TB.h"
int sc_main (int argc , char *argv[]) {
   sharedBusPutGet_TB Mux("Muilti Destination Multi Buffer Channel");
   sc_start();
   //wait(35, SC_NS);
   return 0;
}

