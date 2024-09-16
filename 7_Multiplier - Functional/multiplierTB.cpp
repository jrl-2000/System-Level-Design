#include "multiplierTB.h"

void multiplierTB::resetting()
{
	while (true)
	{
		wait(7, SC_NS);
		rst = SC_LOGIC_0;
		wait(11, SC_NS);
		rst = SC_LOGIC_1;
		wait(58, SC_NS);
		rst = SC_LOGIC_0;
		wait();
	}
}

void multiplierTB::clocking()
{
	while (true)
	{
		wait(17, SC_NS);
		clk = SC_LOGIC_0;
		wait(17, SC_NS);
		clk = SC_LOGIC_1;
	}
}

void multiplierTB::inGenerating()
{
	while (true)
	{
		A = "00000000";
		B = "00000000";
		go = SC_LOGIC_0;
		wait(60, SC_NS);
		
		A = "00000011";
		B = "00000010";		
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;		

		wait(500, SC_NS);
		A = "00001010";
		B = "01000000";
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;

		wait(500, SC_NS);
		A = "00000110";
		B = "00010100";
		go = SC_LOGIC_0;

		wait(120, SC_NS);
		A = "00000110";
		B = "01010100";
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;

		wait();
	}
}

void multiplierTB::displaying()
{
	while (true){
		if (ready == '1')
			cout << A << " * " << B << " = " << Result << " - Time : " << sc_time_stamp() << endl;
		wait();
	}
}
