#include "simpleHierarchical.h"

int main()
{
	int ij;

	bus aData;
	bus bData;
	bus cData;
	bus cOut;
	bus sOut;

	oneBitAdder* FA1 = new oneBitAdder(aData, bData, cData, cOut, sOut);

	do{
		cout << "Enter a, b, c: ";
		cin >> aData >> bData >> cData;
		
		FA1->evl();

		cout << "Carry and Sum: " << cOut << " " << sOut << "\n";

		cout << "\n" << "Continue (0 or 1)?"; cin >> ij;
	} while (ij >0);
}
