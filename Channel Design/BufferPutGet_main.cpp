
#pragma once
#include "BufferPutGet_TB.h"

int sc_main(int argc, char* argv[]) {
	BufferPutGet_TB FPG1("multiBufferPutGet1");
	sc_start(); 
	return 0; 
}