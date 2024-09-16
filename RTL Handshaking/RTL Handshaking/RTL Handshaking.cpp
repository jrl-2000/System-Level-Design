#include "RTL Handshaking.h"

void RTLhandshaking::S2Ptransition() {
	if (clk->event() && clk == '1')
		switch (S2Pstate) {
		case go1Wait:
			if (go == '1') S2Pstate = go0Wait;
			else S2Pstate = go1Wait;
			break;
		case go0Wait:
			if (go == '0') S2Pstate = count8Bits;
			else S2Pstate = go0Wait;
			countBits = 0;
			break;
		case count8Bits:
			if (countBits.read().to_uint() == 7) S2Pstate = got8Bits;
			else S2Pstate = count8Bits;
			collectBits = (serIn, collectBits.read().range(7, 1));
			countBits = countBits.read().to_uint() + 1;
			break;
		case got8Bits:
			if (parAccepted == '1') S2Pstate = go1Wait;
			else S2Pstate = got8Bits;
			break;
		default:
			break;
	}
}
void RTLhandshaking::S2Psignals() {
	ready = SC_LOGIC_0;
	parReady = SC_LOGIC_0;
	if (S2Pstate == go1Wait) ready = SC_LOGIC_1;
	else if (S2Pstate == got8Bits) parReady = SC_LOGIC_1;
}

void RTLhandshaking::W2Stransition() {
	if (clk->event() && clk == '1')
		switch (W2Sstate) {
		case par1Wait:
			if (parReady == '1') W2Sstate = par0Wait;
			else W2Sstate = par1Wait;
			break;
		case par0Wait:
			if (parReady == '0') W2Sstate = pushData;
			else W2Sstate = par0Wait;
			break;
		case pushData:
			W2Sstate = par1Wait;
			break;
		default:
			break;
	}
}
void RTLhandshaking::W2Ssignals() {
	push = SC_LOGIC_0;
	parAccepted = SC_LOGIC_0;
	stackData = 0;
	if (W2Sstate == par0Wait) {
		parAccepted = SC_LOGIC_1;
		stackData = collectBits;
	}
	else if (W2Sstate == pushData) {
		push = SC_LOGIC_1;
		stackData = collectBits;
	}
}
