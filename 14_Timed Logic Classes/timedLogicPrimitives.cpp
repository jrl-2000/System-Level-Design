#include "timedLogicPrimitives.h"
#include "timedLogicFunctions.h"

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

void AND::evl () {

	if ((i1->value == '0') || (i2->value == '0')) 
		o1->value = '0';
	else if ((i1->value == '1') && (i2->value == '1')) 
		o1->value = '1';
	else 
		o1->value='X';

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, i2->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + i2->activityCount +
		((lastValue == o1->value) ? 0 : 1);
	
	lastEvent = o1->eventTime;
	lastValue = o1->value; 
}

void OR::evl () {

	if ((i1->value == '1') || (i2->value == '1')) 
		o1->value = '1';
	else if ((i1->value=='0')&&(i2->value=='0')) 
		o1->value='0';
	else 
		o1->value='X';

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, i2->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + i2->activityCount +
		((lastValue == o1->value) ? 0 : 1);

	lastEvent = o1->eventTime; 
	lastValue = o1->value;
}

void NOT::evl () {

	if (i1->value=='0') 
		o1->value='1';
	else if (i1->value=='1') 
		o1->value='0';
	else 
		o1->value='X';

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + 
		((lastValue == o1->value) ? 0 : 1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}

void XOR::evl () {

	if ((i1->value == 'X') || (i2->value == 'X') ||
		(i1->value == 'Z') || (i2->value == 'Z')) 
		o1->value = 'X';
	else if (i1->value==i2->value) 
		o1->value='0';
	else 
		o1->value='1';

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, i2->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + i2->activityCount +
		((lastValue == o1->value) ? 0 : 1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
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

}

// Structures based on above primitives begin here

void fullAdder::evl () {

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

void halfAdder::evl () {
	
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
