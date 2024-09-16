#include "inheritedLogicClassesPrimitives.h"
#include "inheritedLogicClassesFunctions.h"

#define MAX(a,b) ((a>b)?a:b)

int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int in2LastEvent, int gateDelay, int lastEvent){

	if (lastValue == newValue) 
		return lastEvent;
	else 
		return gateDelay + MAX (in1LastEvent, in2LastEvent);
}

int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int gateDelay, int lastEvent){

	if (lastValue == newValue) 
		return lastEvent;
	else 
		return gateDelay + in1LastEvent;
}

void gates::evl() { // inverts its input 1

	if (i1->value == '0')
		o1->value = '1';
	else if (i1->value == '1')
		o1->value = '0';
	else
		o1->value = 'X';

	gates::timingActivity1();
}
void gates::timingActivity2() {

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, i2->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + i2->activityCount +
		((lastValue == o1->value) ? 0 : 1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}
void gates::timingActivity1() {

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + ((lastValue == o1->value)?0:1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}

void AND::evl() {

	if ((i1->value == '0') || (i2->value == '0'))
		o1->value = '0';
	else if ((i1->value == '1') && (i2->value == '1'))
		o1->value = '1';
	else
		o1->value = 'X';

	gates::timingActivity2();
}

void OR::evl() {

	if ((i1->value == '1') || (i2->value == '1')) 
		o1->value = '1';
	else if ((i1->value=='0')&&(i2->value=='0')) 
		o1->value='0';
	else 
		o1->value='X';

	gates::timingActivity2();
}

/*void not::evl () { // uses gates::evl(); }*/

void XOR::evl () {

	if ((i1->value == 'X') || (i2->value == 'X') ||
		(i1->value == 'Z') || (i2->value == 'Z')) 
		o1->value = 'X';
	else if (i1->value==i2->value) 
		o1->value='0';
	else 
		o1->value='1';

	gates::timingActivity2();
}

void dff_ar::evl() {

	if (R->value == '1') {
		Q->value = '0';
		Q->eventTime = calculateEventTime(lastValue, Q->value,
			R->eventTime, rstQDelay, lastEvent);
	}
	else if (clk->value == 'P') {
		Q->value = D->value;
		Q->eventTime = calculateEventTime(lastValue, Q->value,
			clk->eventTime, clkQDelay, lastEvent);
	}
	Q->activityCount = D->activityCount + 2 +
		((lastValue == Q->value) ? 0 : 3);

	lastEvent = Q->eventTime;
	lastValue = Q->value;
}

// Structures based on above primitives begin here
void TwoBitComp::evl() {
	a0l = *ia0;
	a1l = *ia1;
	b0l = *ib0;
	b1l = *ib1;

	// Evaluate gates in the proper order
	not1->evl();
	not2->evl();
	not3->evl();
	not4->evl();

	xor1->evl();
	xor2->evl();
	not5->evl();
	not6->evl();

	and1->evl();

	and2->evl();
	and4->evl();
	and5->evl();
	and7->evl();
	and8->evl();

	or1->evl();
	or2->evl();

	and9->evl();
	and10->evl();
	and11->evl();
	and12->evl();
	and13->evl();

	or3->evl();
	or4->evl();

	// Take calculated local wire values and assign the values 
	// to the outside wires via pointers of FA
	*oL = lt;
	*oG = gt;
	*oE = et;
}

void EightBitComp::evl() {
	a0L = *ia0;
	a1L = *ia1;
	a2L = *ia2;
	a3L = *ia3;
	a4L = *ia4;
	a5L = *ia5;
	a6L = *ia6;
	a7L = *ia7;
	b0L = *ib0;
	b1L = *ib1;
	b2L = *ib2;
	b3L = *ib3;
	b4L = *ib4;
	b5L = *ib5;
	b6L = *ib6;
	b7L = *ib7;

	TwoBitCompHigh0->evl();
	TwoBitCompHigh1->evl();
	TwoBitCompLow2->evl();
	TwoBitCompLow3->evl();

	and1->evl();
	and2->evl();
	and3->evl();
	and4->evl();
	and5->evl();

	or1->evl();
	or2->evl();

	and6->evl();
	and7->evl();

	or3->evl();
	or4->evl();

	and8->evl();

	or5->evl();
	and9->evl();

	or6->evl();

	*oL = LT;
	*oG = GT;
	*oE = ET;
}


void fullAdder::evl () {

	// Via the FA pointers, read wire values that connect to
	// the FA from outside, and assign them to FA Local wires
	aL = *i1; bL = *i2; ciL = *i3;
	and1->timingActivity1();
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

void halfAdder::evl () {
	
	// Via the HA pointers, read wire values that connect to
	// the HA from outside, and assign them to HA Local wires
	aL = *i1; bL = *i2; 

	// Evaluate gates in the proper order
	and1->evl();
	xor1->evl();

	// Take calculated local wire values and assign the values 
	// to the outside wires via pointers of FA
	*o1 = coL; *o2 = sumL;
}

// --------------------- Vector Logics -------------------- //

wireV::wireV(string v, int d, int size) : eventTime(d), n(size) {
	int i;
	value = new char[n + 1];
	v.resize(n, 'X');
	for (i = 0; i < n; i++){ *(i + value) = v.at(i); };
	*(n + value) = '\0';
}
void wireV::put(string a, int d){
	int i;
	eventTime = d;
	a.resize(n, '0');
	for (i = 0; i < n; i++){ *(i + value) = a.at(i);};
}
void wireV::get(string& a, int& d){
	int i;
	d = eventTime;
	a.resize(n, '0');
	for (i = 0; i < n; i++){ a.at(i) = *(i + value); };
}

void andV::evl() {
	int i = 0;

	while (i1->value[i] != '\0'){
		if (((i1->value[i]) == '0') || ((i2->value[i]) == '0'))
			o1->value[i] = '0';
		else if ((i1->value[i] == '1') && (i2->value[i] == '1'))
			o1->value[i] = '1';
		else
			o1->value[i] = 'X';
		i++;
	};
}

void orV::evl() {
	int i = 0;
	while (i1->value[i] != '\0'){
//		if (((i1->value[i]) == '1') || ((i2->value[i]) == '1'))
		if ((*(i1->value + i) == '1') || (*(i2->value + i) == '1'))
			o1->value[i] = '1';
		else if ((i1->value[i] == '0') && (i2->value[i] == '0'))
			o1->value[i] = '0';
		else
			o1->value[i] = 'X';
		i++;
	};
}

