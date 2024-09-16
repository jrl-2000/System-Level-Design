#include "timedOperators.h"

tlogic operator& (tlogic a, tlogic b)
{
	tlogic tl;
	if ((a.logic=='0')||(b.logic=='0')) {
		tl.logic = '0';
		if (a.logic=='0') tl.time = a.time;
		else tl.time = b.time;
	}
	else if ((a.logic=='1')&&(b.logic=='1')) {
		tl.logic = '1';
		if (a.time > b.time) tl.time = a.time;
		else tl.time = b.time;
	}
	else {
		tl.logic = 'X';
		if (a.logic != '1') tl.time = a.time;
		else tl.time = b.time;
	};
	return tl;
}

tlogic operator| (tlogic a, tlogic b)
{
	tlogic tl;
	if ((a.logic=='1')||(b.logic=='1')) {
		tl.logic = '1';
		if (a.logic=='1') tl.time = a.time;
		else tl.time = b.time;
	}
	else if ((a.logic=='0')&&(b.logic=='0')) {
		tl.logic = '0';
		if (a.time > b.time) tl.time = a.time;
		else tl.time = b.time;
	}
	else {
		tl.logic = 'X';
		if (a.logic != '0') tl.time = a.time;
		else tl.time = b.time;
	};
	return tl;
}

tlogic operator~ (tlogic a)
{
	tlogic tl;
	if (a.logic=='1') tl.logic = '0';
	else if (a.logic=='0') tl.logic = '1';
	else tl.logic=='X';
	tl.time = a.time;
	return tl;
}

tlogic operator^ (tlogic a, tlogic b)
{
	tlogic tl;
	if (a.logic==b.logic) tl.logic = '0';
	else tl.logic = '1';
	if (a.time > b.time) tl.time = a.time;
	else tl.time = b.time;
	return tl;
}

