#include "sinhxTB.h"

void HyperbolicSineTB::resetting()
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

void HyperbolicSineTB::clocking()
{
	while (true)
	{
		wait(17, SC_NS);
		clk = SC_LOGIC_0;
		wait(17, SC_NS);
		clk = SC_LOGIC_1;
	}
}

void HyperbolicSineTB::inGenerating()
{
	while (true)
	{
		inHSU = 5.0;
		startHSU = SC_LOGIC_0;
		wait(60, SC_NS);

		inHSU = 5.0;
		startHSU = SC_LOGIC_1;
		wait(60, SC_NS);
		startHSU = SC_LOGIC_0;
		wait(10, SC_NS);

	}
}

void HyperbolicSineTB::displaying()
{
    while (true){
		if (readyHSU == '1')
			cout << " Input " << inHSU << " Is " << outHSU << " Result " << sc_time_stamp() << endl;
		wait();
	}
}

