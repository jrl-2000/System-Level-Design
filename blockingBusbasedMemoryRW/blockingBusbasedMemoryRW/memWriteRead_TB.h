#include "memWriteRead.h"
#include "memoryUnit.h"

SC_MODULE (memWriteRead_TB) {
	memWriterReader* MW1;
	memoryUnit* MU1;

	SC_CTOR(memWriteRead_TB)
		{
		MU1 = new memoryUnit("memoryUnit");
			// MU1->memSideBus(*MU1->membus); // This is in memoryUnit
		MW1 = new memWriterReader("memoryWriter");
			MW1->memWriterReaderBus(*MU1->membus);
	}
};
