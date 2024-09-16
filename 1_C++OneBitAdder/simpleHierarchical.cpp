#include "simpleHierarchical.h"

void XORgate::evl() {
	if (*i1 == *i2)
		o1->fill('0');
	else
		o1->fill('1');
}

void AO2gate::evl() {
	if ((*i1 && *i2) || (*i3 && *i4))
		o1->fill('1');
	else
		o1->fill('0');
}

oneBitAdder::oneBitAdder(bus& ai, bus& bi, bus& ci, bus& co, bus& su) 
	:
	i1(&ai), i2(&bi), i3(&ci), o1(&co), o2(&su)
{
	XORa = new XORgate(*i1, *i2, x1);
	XORb = new XORgate(x1, *i3, *o2);
	AO2a = new AO2gate(*i1, *i2, x1, *i3, *o1);
}
void oneBitAdder::evl() {
	XORa->evl();
	AO2a->evl();
	XORb->evl();
}

