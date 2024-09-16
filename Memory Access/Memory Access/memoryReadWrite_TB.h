#include "memoryReadWrites.h"

SC_MODULE(memoryAccess_TB) {

	memoryAccess<sc_lv<8>, 4> * memBus;
	initiators<0, 9, 0>* INI0;
	initiators<1, 1111, 0>* INI1;
	initiators<2, 117, 0>* INI2;
	initiators<3, 1115, 0>* INI3;
	memory<0, 17, 0>* MEM0;

	SC_CTOR(memoryAccess_TB) {
		memBus = new memoryAccess<sc_lv<8>, 4>;

		INI0 = new initiators<0, 9, 0>("Initiator0");
		INI0->out(*memBus);
		INI1 = new initiators<1, 1111, 0>("Initiator1");
		INI1->out(*memBus);
		INI2 = new initiators<2, 117, 0>("Initiator2");
		INI2->out(*memBus);
		INI3 = new initiators<3, 1115, 0>("Initiator3");
		INI3->out(*memBus);

		MEM0 = new memory<0, 17, 0>("Memory0");
		MEM0->in(*memBus);
	}
};

