#include "burstReaderWriter.h"

void writer::writeBlocks()
{
	sc_lv<64> dataToWrite;
	sc_lv<13> startAddress;

	for (int j = 0; j <= 2; j++){

		startAddress = (sc_lv<13>)(rand() % 127);
		dataToWrite.range(63, 32) = rand();
		dataToWrite.range(31,  0) = rand();
		cout << "Initiated write at address:" << startAddress.to_uint() 
			 << " data:" << dataToWrite << '\n';
		out->burstWrite(startAddress, dataToWrite);
		cout << "At " << sc_time_stamp() << " write completed at:" 
			 << startAddress << " data:" << dataToWrite << '\n';
		wait(13, SC_NS);
	}
}

void reader::readBlocks()
{
	sc_lv<64> dataRead;
	sc_lv<13> startAddress;

	for (int j = 0; j <= 2; j++){

		startAddress = (sc_lv<13>)(rand() % 127);
		cout << "Initiated read from address:" << startAddress.to_uint() << '\n';
		in->burstRead(startAddress, dataRead);
		cout << "At " << sc_time_stamp() << " read completed from:"
			<< startAddress << " data:" << dataRead << '\n';
		wait(53, SC_NS);
	}
}

