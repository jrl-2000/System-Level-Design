#include "timedPrimitives.h"

tlogic AND (tlogic a, tlogic b, int delay)
{
	tlogic tl;
	if ((a.logic=='0')||(b.logic=='0')) {
		tl.logic = '0';
		if (a.logic=='0') tl.time = a.time + delay;
		else tl.time = b.time + delay;
	}
	else if ((a.logic=='1')&&(b.logic=='1')) {
		tl.logic = '1';
		if (a.time > b.time) tl.time = a.time + delay;
		else tl.time = b.time + delay;
	}
	else {
		tl.logic = 'X';
		if (a.logic != '1') tl.time = a.time + delay;
		else tl.time = b.time + delay;
	};
	return tl;
}

tlogic OR (tlogic a, tlogic b, int delay)
{
	tlogic tl;
	if ((a.logic=='1')||(b.logic=='1')) {
		tl.logic = '1';
		if (a.logic=='1') tl.time = a.time + delay;
		else tl.time = b.time + delay;
	}
	else if ((a.logic=='0')&&(b.logic=='0')) {
		tl.logic = '0';
		if (a.time > b.time) tl.time = a.time + delay;
		else tl.time = b.time + delay;
	}
	else {
		tl.logic = 'X';
		if (a.logic != '0') tl.time = a.time + delay;
		else tl.time = b.time + delay;
	};
	return tl;
}

tlogic NOT (tlogic a, int  delay)
{
	tlogic tl;
	if (a.logic=='1') tl.logic = '0';
	else if (a.logic=='0') tl.logic = '1';
	else tl.logic=='X';
	tl.time = a.time + delay;
	return tl;
}

tlogic XOR (tlogic a, tlogic b, int delay)
{
	tlogic tl;
	if (a.logic==b.logic) tl.logic = '0';
	else tl.logic = '1';
	if (a.time > b.time) tl.time = a.time + delay;
	else tl.time = b.time + delay;
	return tl;
}
