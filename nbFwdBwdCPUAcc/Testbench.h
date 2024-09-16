#include "Processor.h"
#include "Accelerator.h"

SC_MODULE(Testbench)
{
	Processor *CPU;
	Accelerator *Acc;

	SC_CTOR(Testbench)
	{
		CPU = new Processor("Processor");
		Acc = new Accelerator("Accelerator");
 		   CPU->procSocket.bind(Acc->accSocket);
	}
};

