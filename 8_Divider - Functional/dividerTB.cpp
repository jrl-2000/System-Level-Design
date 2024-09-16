#include "dividerTB.h"

void dividerTB::resetting()
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

void dividerTB::clocking()
{
	while (true)
	{
		wait(17, SC_NS);
		clk = SC_LOGIC_0;
		wait(17, SC_NS);
		clk = SC_LOGIC_1;
	}
}

void dividerTB::inGenerating()
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
		A = "01000000";
		B = "00001010";
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;

		wait(500, SC_NS);
		A = "01010100";
		B = "00000110";
		go = SC_LOGIC_1;
		wait(60, SC_NS);
		go = SC_LOGIC_0;

		wait();
	}
}

void dividerTB::displaying()
{
    while (true){
		if (ready == '1')			
			cout << A << " / " << B << " => Quotient = " << Q << " & Remainder = " << R << " - Time : " << sc_time_stamp() << endl;
		wait();
	}	
}

