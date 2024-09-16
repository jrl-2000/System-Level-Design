#include "controller_avg.h"

void controller::comb_O_function()
{


	switch (p_state) {
	case INITIALIZE:
		ready = SC_LOGIC_0;
		break;
	case WAIT_ON_START:
		ready = SC_LOGIC_0;
		break;
	case COUNT1:
		ready = SC_LOGIC_0;
		load1 = SC_LOGIC_1;
		break;
	case COUNT2:
		ready = SC_LOGIC_0;
		load2 = SC_LOGIC_1;
		break;
	case COUNT3:
		ready = SC_LOGIC_0;
		load3 = SC_LOGIC_1;
		break;
	case COUNT4:
		ready = SC_LOGIC_0;
		load4 = SC_LOGIC_1;
		break;
	case COUNT5:
		ready = SC_LOGIC_0;
		load5 = SC_LOGIC_1;
		break;
	case COUNT6:
		ready = SC_LOGIC_0;
		load6 = SC_LOGIC_1;
		break;
	case COUNT7:
		ready = SC_LOGIC_0;
		load7 = SC_LOGIC_1;
		break;
	case COUNT8:
		ready = SC_LOGIC_0;
		load8 = SC_LOGIC_1;
		break;
	case COUNT9:
		ready = SC_LOGIC_0;
		load9 = SC_LOGIC_1;
		break;
	case COUNT10:
		ready = SC_LOGIC_0;
		load10 = SC_LOGIC_1;
		break;
	case READY:
		ready = SC_LOGIC_1;
		break;
	default:
		ready = SC_LOGIC_0;
		load1 = SC_LOGIC_0;
		load2 = SC_LOGIC_0;
		load3 = SC_LOGIC_0;
		load4 = SC_LOGIC_0;
		load5 = SC_LOGIC_0;
		load6 = SC_LOGIC_0;
		load7 = SC_LOGIC_0;
		load8 = SC_LOGIC_0;
		load9 = SC_LOGIC_0;
		load10 = SC_LOGIC_0;
		break;
	}



}
void controller::comb_S_function() {
	//count = 0;
	n_state = INITIALIZE;
	switch (p_state) {
	case INITIALIZE:
		if (start == '0')
			n_state = INITIALIZE;
		else
			n_state = WAIT_ON_START;
		break;
	case WAIT_ON_START:
		if (start == '0')
			n_state = COUNT1;
		else
			n_state = WAIT_ON_START;
		break;
	case COUNT1:
		n_state = COUNT2;
		break;
	case COUNT2:
		n_state = COUNT3;
		break;
	case COUNT3:
		n_state = COUNT4;
		break;
	case COUNT4:
		n_state = COUNT5;
		break;
	case COUNT5:
		n_state = COUNT6;
		break;
	case COUNT6:
		n_state = COUNT7;
		break;
	case COUNT7:
		n_state = COUNT8;
		break;
	case COUNT8:
		n_state = COUNT9;
		break;
	case COUNT9:
		n_state = COUNT10;
		break;
	case COUNT10:
		n_state = READY;
		break;
	case READY:
		n_state = INITIALIZE;
		break;
	default:
		n_state = INITIALIZE;
		break;
	}
	//cntr.write(count);
}

void controller::seq_function() {
	while (1) {
		if (rst == '1')
			p_state = INITIALIZE;
		else if (clk->event() && (clk == '1'))
			p_state = n_state;
		wait();
	}
}

