#include "primitives.h"

bool AND (bool a, bool b)
{
	return (a && b);
}

bool OR (bool a, bool b)
{
	return (a || b);
}

bool NOT (bool a)
{
	return (!a);
}

bool NAND (bool a, bool b)
{
	return (!(a && b));
}

bool NOR (bool a, bool b)
{
	return (!(a || b));
}

bool XOR (bool a, bool b)
{
	return ((!a && b) || (a && !b));
}

void AND (bool a, bool b, bool& w)
{
	w = a && b;
}

void OR (bool a, bool b, bool& w)
{
	w = a || b;
}

void NOT (bool a, bool& w)
{
	w = ! a;
}

void NAND (bool a, bool b, bool& w)
{
	w = !(a && b);
}

void NOR (bool a, bool b, bool& w)
{
	w = !(a || b);
}

void XOR (bool a, bool b, bool& w)
{
	w = (a != b);
}

bool logic (bool a, bool b, void (*f) (bool, bool, bool&))
{
	bool w;
	(*f) (a, b, w);
	return (w);
}

//

bool AND5 (bool a, bool b, bool c, bool d, bool e) 
{
	return (a && b && c && d && e);
}

bool OR5 (bool a, bool b, bool c, bool d, bool e)
{
	return (a || b || c || d || e);
}

bool XOR5 (bool a, bool b, bool c, bool d, bool e)
{
	return ( a != b != c != d != e );
}

//
void AND (bool a[], bool b[], bool w[], const int SIZE)
{
	int i;
	for (i=0; i<=SIZE; i++) {
		w[i] = AND(a[i], b[i]);
	}
}

void OR (bool a[], bool b[], bool w[], const int SIZE)
{
	int i;
	for (i=0; i<=SIZE; i++) {
		w[i] = OR(a[i], b[i]);
	}
}