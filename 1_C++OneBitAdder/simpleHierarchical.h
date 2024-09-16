#include "classVectorPrimitives.h"
#include <string>
using namespace std;

class XORgate {
	bus *i1, *i2, *o1;
public:
	XORgate(bus& a, bus& b, bus& xo) :
		i1(&a), i2(&b), o1(&xo)
	{
		o1->fill('X');
	}
	~XORgate();
	void evl();
};

class AO2gate {
	bus *i1, *i2, *i3, *i4, *o1;
public:
	AO2gate(bus& a, bus& b, bus& c, bus& d, bus& ao) :
		i1(&a), i2(&b), i3(&c), i4(&d), o1(&ao)
	{
		o1->fill('X');
	}
	~AO2gate();
	void evl();
};

class oneBitAdder {
	bus	*i1, *i2, *i3, 
		*o1, *o2;

	XORgate* XORa;
	XORgate* XORb;
	AO2gate* AO2a;

	bus x1;

public:
	oneBitAdder(bus& ai, bus& bi, bus& ci, bus& co, bus& su);
	~oneBitAdder();
	void evl();
};
