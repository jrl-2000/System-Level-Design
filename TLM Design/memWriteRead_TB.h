#include "memWriteRead.h"
#include "memoryUnit.h"

SC_MODULE (memWriteRead_TB) {
	memWriterReader* MW1;
	memoryArray* MU1;
	Interconnect* IN1;


	SC_CTOR(memWriteRead_TB)
		{
			MW1 = new memWriterReader("memoryWriter");
			MU1 = new memoryArray("memoryArray");
			IN1 = new Interconnect("Interconect");
			MW1->memWriterReaderSocket.bind(IN1->memSideSocket1);
			IN1->memWriterReaderSocket1.bind(MU1->memSideSocket);
			//MW1->memWriterReaderSocket.bind( MU1->memSideSocket );
	}
};
