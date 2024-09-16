#include "class2PointerPrimitives.h"
#include "class2Pointerfunctions.h"

AND::AND() {}
void AND::evl () {
	if ((*i1=='0')||(*i2=='0')) *o1='0';
	else if ((*i1=='1')&&(*i2=='1')) *o1='1';
	else *o1='X';
}

OR::OR() {}
void OR::evl () {
	if ((*i1=='1')||(*i2=='1')) *o1='1';
	else if ((*i1=='0')&&(*i2=='0')) *o1='0';
	else *o1='X';
}

NOT::NOT() {}
void NOT::evl () {
	if (*i1=='0') *o1='1';
	else if (*i1=='1') *o1='0';
	else *o1='X';
}

XOR::XOR() {}
void XOR::evl () {
	if ((*i1=='X')||(*i2=='X')||(*i1=='Z')||(*i2=='Z')) *o1='X';
	else if (*i1==*i2) *o1='0';
	else *o1='1';
}

fullAdder::fullAdder() {}
void fullAdder::evl () {

	// fulladder Local wires
	char aL('X'), bL('X'), ciL('X');
	char coL('X'), sumL('X');
	char axbL('X'), abL('X'), abcL('X');
	
	// Declare necessary gate instances
	XOR *xor1=new XOR;
	XOR *xor2=new XOR;
	AND *and1=new AND;
	AND *and2=new AND;
	OR  *or1= new OR;

	// Associate ports of the gates with the Local FA wires
	xor1->ios(aL, bL, axbL);
	and1->ios(aL, bL, abL);
	and2->ios(axbL, ciL, abcL);
	or1->ios(abL, abcL, coL);
	xor2->ios(axbL, ciL, sumL);

	// Via the FA pointers, read wire values that connect to
	// the FA from outside, and assign them to FA Local wires
	aL = *i1; bL = *i2; ciL = *i3;

	// Evaluate gates in the proper order
	xor1->evl();
	and1->evl();
	and2->evl();
	or1->evl();
	xor2->evl();
		
	// Take calculated local wire values and assign the values 
	// to the outside wires via pointers of FA
	*o1 = coL; *o2 = sumL;
}

halfAdder::halfAdder() {}
void halfAdder::evl () {
	// halfadder Local wires
	char aL('X'), bL('X');
	char coL('X'), sumL('X');

	// Declare necessary gate instances
	XOR *xor1 = new XOR;
	AND *and1 = new AND;

	// Associate ports of the gates with the Local HA wires
	xor1->ios(aL, bL, sumL);
	and1->ios(aL, bL, coL);

	// Via the HA pointers, read wire values that connect to
	// the HA from outside, and assign them to HA Local wires
	aL = *i1; bL = *i2; 

	// Evaluate gates in the proper order
	xor1->evl();
	and1->evl();

	// Take calculated local wire values and assign the values 
	// to the outside wires via pointers of FA
	*o1 = coL; *o2 = sumL;

}
