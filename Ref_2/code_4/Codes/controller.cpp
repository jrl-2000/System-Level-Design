#include "controller.h"

void controller::output_function()
{
	// Inactive output values
	lddata = SC_LOGIC_0;
	ready = SC_LOGIC_0;
	
	switch( p_state ){
		case IDLE:
			lddata = SC_LOGIC_0;
			ready = SC_LOGIC_1;
			count = 0;
			break;
		case INIT: 
			lddata = SC_LOGIC_0;
			ready = SC_LOGIC_0;
			count = 0;
			break;
		case GETD: 
			lddata = SC_LOGIC_1;
			ready = SC_LOGIC_0;
			count++;
			break;
		default: 
			lddata = SC_LOGIC_0;
			ready = SC_LOGIC_0;
			count = 0;
			break;
	}
}
void controller::state_function(){
	n_state = IDLE;
	switch( p_state ){
		case IDLE:
			if (start == '0')
				n_state = IDLE;
			else
				n_state = INIT;
			break;
		case INIT: 
			if(start == '0') 
				n_state = GETD;
			else
				n_state = INIT;
			break;
		case GETD: 
			if (count < 7)
				n_state = GETD;
			else
				n_state = IDLE;
			break;
		default: 
			n_state = IDLE;
			break;
	}
}

void controller::seq_function(){
	while (1){
		if (rst == '1')
			p_state = IDLE;
		else if (clk->event() &&(clk =='1'))
			p_state = n_state;
		wait();
	}
}
