#include <systemc.h>

class burst_write_if: virtual public sc_interface
	{
		public:
			virtual void burstWrite(sc_lv<13> address, sc_lv<64> data ) = 0;
};

class burst_read_if: virtual public sc_interface
	{
		public:
			virtual void burstRead(sc_lv<13> address, sc_lv<64>& data) = 0;
};

