#include "vectorPrimitives.h"
#include "vectorFunctions.h"

void getBits (string vectorName, int numBits, bool values[])
{
	string valuesS;
	int i;
	cout << "Enter " << numBits << " bits of " << vectorName << ": "; 
	cin >> valuesS;
	for (i=0; i<numBits; i++){
		if (valuesS[i] == '1') values[i] = true; 
		else values[i] = false;
	}
}

void putBits (string vectorName,  int numBits, bool values[])
{
	int i;
		
	cout << vectorName << ": ";
	for (i=0; i<numBits; i++){
		cout << values[i]; // outputs integer 
	}
	cout << "\n";
		
}
void two2OneMux (bool a[], bool b[], bool w[], bool sel, int SIZE=8)
{
	bool as [8];
	bool bs [8];
	
	int i;
	for (i=0; i<SIZE; i++) {
		as[i] = AND (a[i], NOT(sel));
	}
	for (i=0; i<SIZE; i++) {
		bs[i] = AND (b[i], sel);
	}

	OR (as, bs, w, SIZE); 
}

void two2OneMuxB (bool a[], bool b[], bool w[], bool sel, int SIZE=8)
{
	int i;
	for (i=0; i<SIZE; i++) {
		w[i] = sel ? b[i] : a[i];
	}
}

int main ()
{
	bool aV [8];
	bool bV [8];
	bool sel;
	bool selV[1];
	bool wV [8];
    int ai;

	do {
		getBits ("aV", 8, aV);
		getBits ("bV", 8, bV);
		getBits ("selV", 1, selV); sel = selV[0];

		cout << "two2OneMux using and, or, not \n";
		two2OneMux (aV, bV, wV, sel, 8);
		
		putBits ("aV", 8, aV);
		putBits ("bV", 8, bV);
		putBits ("wV", 8, wV);

		cout << "two2OneMuxB using ?: \n";
		two2OneMuxB (aV, bV, wV, sel, 8);
		
		putBits ("aV", 8, aV);
		putBits ("bV", 8, bV);
		putBits ("wV", 8, wV);

		cout << "\n" << "Continue (0 or 1)?"; cin >> ai;
	} while (ai>0);
}
