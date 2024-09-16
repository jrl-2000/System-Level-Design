#include "timedPrimitives.h"
#include "timedFunctions.h"

#define MAX(a,b) (a>b?a:b);
#define MIN(a,b) (a<b?a:b);

void getVect (string vectorName, int numBits, tlogic values[])
{ //order according to bit significance (0 index is least)
	string valuesS;
	int i, bits, delay;
	cout << "Enter " << numBits << " bits of " << vectorName << ": ";
	cin >> valuesS;
	bits = MIN (valuesS.length(), numBits); // if fewer are entered
	cout << "Enter vector delay: "; cin >> delay;
	for (i=bits-1; i>=0; i--) {
		values[i].logic = char(valuesS[bits-1-i]); // reverse bits
//		values[i].time = delay; // This or two below are good
//		(*(values+i)).time = delay;
		(values+i)->time = delay;
	}
}

void putVect (string vectorName, int numBits, tlogic values[])
{
	int i, delay;
	delay = 0;
	cout << vectorName << ": ";
	for (i=numBits-1; i>=0; i--) {
		cout << values[i].logic; 
		if (values[i].time > delay) delay=values[i].time;
	}
	cout << " AT " << delay << "\n";
}

void fullAdder (tlogic a, tlogic b, tlogic ci, tlogic& co, tlogic& sum)
{
	tlogic axb, ab, abc;

	axb = XOR (a, b, 5);
	ab  = AND (a, b, 3);
	abc = AND (axb, ci, 3);
	co = OR (ab, abc, 4);
	sum = XOR (axb, ci, 5);
}

void nBitAdder (tlogic a[], tlogic b[], tlogic ci[], tlogic co[], tlogic sum[], int bits)
{
	// assumes 0 is LSB
	int i;
	tlogic* c = new tlogic[bits+1];
	c[0] = ci[0];
	for (i = 0; i<bits; i++)
	{
		fullAdder(a[i], b[i], c[i], c[i+1], sum[i]);
	}
	co[0] = c[bits];
}

int main ()
{
	tlogic *aV, *bV, *ci, *co, *sumV;

	int bits, go(1);

	while (go)
	{
		cout << "Enter number of bits of operations: "; cin >> bits; 
		aV = new tlogic[bits];
		bV = new tlogic[bits];
		ci = new tlogic[1];
		co = new tlogic[1];
		sumV = new tlogic[bits];

		getVect ("aV", bits, aV); putVect ("aV", bits, aV);
		getVect ("bV", bits, bV); putVect ("bV", bits, bV);
		getVect ("ci", 1, ci); putVect ("ci", 1, ci);
		cout << "\n";

		nBitAdder (aV, bV, ci, co, sumV, bits); // calculates all propagations

		putVect ("  aV", bits, aV);	putVect ("  bV", bits, bV);
		putVect ("  ci", 1, ci);
		putVect ("sumV", bits, sumV); putVect ("  co", 1, co);

		delete [] aV;
		delete [] bV;
		delete [] ci;
		delete [] co;
		delete [] sumV;

		cout << "\nEnter 0 to exit: "; cin >> go;
	}
}
