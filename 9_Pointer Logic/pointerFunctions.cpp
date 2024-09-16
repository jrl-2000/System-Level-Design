#include "pointerPrimitives.h"
#include "pointerFunctions.h"

void mux8Std2TO1 (char *a, char *b, char *w, char sel)
{
	int i=0;
	do {
		*(w+i) = (sel=='1') ? *(b+i) : *(a+i);
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}

void mux8Tri2TO1 (char *a, char *b, char *w, char sel, char oe)
{
	int i=0;
	do {
		if (oe == '1') *(w+i) = (sel=='1') ? *(b+i) : *(a+i);
		else *(w+i) = 'Z';
		i++;
	} while (*(a+i) != '\0');
	*(w+i) = '\0';
}

int main ()
{
	char* aC;
	char* bC;
	char sel, oe;

	int ii, ij;

	cout << "Enter number of bits for your operations: "; 
	cin >> ii; 
	aC = new char [ii+1];
	bC = new char [ii+1];
	char* wC = new char [ii+1];
	
	do {
		cout << "Enter " << ii << " (or less) bits of aC: "; 
		cin >> aC; cout << "You entered " << strlen(aC) << " bits (" << aC << ") \n";

		cout << "Enter " << ii << " (or less) bits of bC: "; 
		cin >> bC; cout << "You entered " << strlen(bC) << " bits (" << bC << ") \n";

		cout << "Enter sel <sp> oe: "; 
		cin >> sel >> oe;

		mux8Std2TO1 (aC, bC, wC, sel);
		cout << "Std Mux: " << wC << '\n';
		
		mux8Tri2TO1 (aC, bC, wC, sel, oe);
		cout << "Tri Mux: " << wC << '\n';
		
		AND (aC, bC, wC);
		cout << "and: " << wC << '\n';
		
		OR (aC, bC, wC);
		cout << " or: " << wC << '\n';

		cout << "\n" << "Continue (0 or 1)? "; cin >> ij;
		
	} while (ij>0);
}
