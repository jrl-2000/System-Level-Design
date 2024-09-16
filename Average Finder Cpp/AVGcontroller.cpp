#include "AVGController.h"

AVGController::AVGController(bus& rst_, bus& clk_, bus& cntr_, bus& start_, bus& ready_)
	:
	rst(&rst_), clk(&clk_), cntr(&cntr_), start(&start_), ready(&ready_)
	{
		Nstate = 0;
		Pstate= 0;
		//cntr_.resize(4, 'X');
	}

void AVGController::evl () {

	switch (Pstate){
		case 0: //INITIALIZE
			if( *start == "1" )	Nstate = 1;
			else Nstate = 0;
			break;
		case 1: //WAIT_ON_START
			if(*cntr == "1010" ) Nstate = 2;
			else Nstate = 1;
			break;
		case 2: //CALC_NEXT_TERM_1
			Nstate = 0;
			break;
	 }


	 switch (Pstate){
		case 0 : //INITIALIZE
			*ready = "0"; *cntr  = "0";
			 break;
		case 1: //WAIT_ON_START
			*cntr = *cntr + "1";
			break;
		case 2: //CALC_NEXT_TERM_1
			*ready = "1";
			break;
	 }
	 if (*rst == "1") Pstate = 0;
	 else if (*clk == "P") Pstate = Nstate;
}
