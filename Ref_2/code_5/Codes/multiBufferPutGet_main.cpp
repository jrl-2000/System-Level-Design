/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 5: SystemC channels
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "multiBufferPutGet_TB.h"

int sc_main(int argc, char* argv[]) {
	multiBufferPutGet_TB FPG1("multiBufferPutGet1");
	sc_start(); 
	return 0; 
}