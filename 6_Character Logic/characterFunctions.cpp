#include "characterPrimitives.h"
#include "characterFunctions.h"

void getBits (string vectorName, int numBits, char values[])
{
	string valuesS;
	int i;
	cout << "Enter " << numBits << " bits of " << vectorName << ": ";
	cin >> valuesS;
	for (i=0; i<numBits; i++) values[i] = char(valuesS[i]);
	values[numBits] = '\0';
}

void putBits (string vectorName, int numBits, char values[])
{
	int i;

	cout << vectorName << ": ";
	for (i=0; i<numBits; i++){
		cout << values[i];
	}
	cout << "\n";

}

void mux8Std2TO1 (char a[], char b[], char w[], char sel)
{
	int i=0;
	do {
		w[i] = (sel=='1') ? b[i] : a[i];
	} while (a[i++] != '\0');
}

void mux8Tri2TO1 (char a[], char b[], char w[], char sel, char oe)
{
	char selB, selB_oe, sel_oe;
	char asel [9];
	char bsel [9];

	selB = NOT(sel);
	selB_oe = AND(selB, oe);
	sel_oe = AND(sel, oe);
	tri(a, selB_oe, asel);
	tri(b, sel_oe, bsel);
	resolve(asel, bsel, w);
}

int main ()
{
	char aC [9];
	char bC [9];

	char sel;
	char oe;
	
	char wC [9];
    int ai;
	
	do {

		cout << "Enter eight bits of aC: "; cin >> aC; 
		cout << "You entered " << strlen(aC) << " bits: " << aC << "\n";

		cout << "Enter eight bits of bC: "; cin >> bC; 
		cout << "You entered " << strlen(bC) << " bits: " << bC << "\n";

		cout << "Enter sel: "; cin >> sel; 

		cout << "Enter oe: "; cin >> oe;

		mux8Std2TO1 (aC, bC, wC, sel);
		cout << "The " << strlen(wC) << " bits of wC become as follows: \n";
		cout << "Standard Mux:" << wC << '\n';

		mux8Tri2TO1 (aC, bC, wC, sel, oe);
		cout << "Tristate Mux:" << wC << '\n';

		AND (aC, bC, wC);
		cout << "and:" << wC << '\n'; 

		OR (aC, bC, wC);
		cout << "or: " << wC << '\n';

		cout << "\n" << "Continue (0 or 1)?"; cin >> ai;

	} while (ai>0);
}


/*
int main ()
{
	char aC [9];
	char bC [9];
	char sV [2];
	char oV [2];
	char sel;
	char oe;

	char wC [9];
    int ai;

	do {

		getBits ("aV", 8, aC); putBits ("aV", 8, aC);
		getBits ("bV", 8, bC); putBits ("bV", 8, bC);
		getBits ("selV", 1, sV); sel = sV[0];
		getBits ("oeV", 1, oV); oe = oV[0];

		mux8Std2TO1 (aC, bC, wC, sel);
		cout << "Standard Mux:" << wC << '\n';
		putBits ("Standard Mux (putbits)", 8, wC);

		mux8Tri2TO1 (aC, bC, wC, sel, oe);
		putBits ("Tristate Mux (putbits)", 8, wC);

		AND (aC, bC, wC);
		putBits ("and vector: ", 8, wC);

		OR (aC, bC, wC);
		putBits ("or vector: ", 8, wC);

		cout << "\n" << "Continue?"; cin >> ai;

	} while (ai>0);
}
*/
