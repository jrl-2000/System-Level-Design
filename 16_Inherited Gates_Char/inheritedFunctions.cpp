#include "inheritedPrimitives.h"
#include "inheritedFunctions.h"

void fullAdder (char a, char b, char ci, char & co, char & sum)
{
	char axb, ab, abc;
	XOR xor1, xor2;
	AND and1, and2;
	OR or1;

	xor1.inp(a, b); 
		xor1.evl();
		xor1.out(axb);
	and1.inp(a, b); 
		and1.evl();
		and1.out(ab);
	and2.inp(axb, ci); 
		and2.evl();
		and2.out(abc);
	or1.inp(ab, abc); 
		or1.evl();
		or1.out(co);
	xor2.inp(axb, ci); 
		xor2.evl();
		xor2.out(sum);
}


int main ()
{
	char aC;
	char bC;
	char ciC;
	char coC;
	char sumC;

    int ai;

	do {

		cout << "Enter a: ";
		cin >> aC; cout << aC << '\n';

		cout << "Enter b: ";
		cin >> bC; cout << bC << '\n';

		cout << "Enter ci: ";
		cin >> ciC; cout << ciC << '\n';

		fullAdder (aC, bC, ciC, coC, sumC);
		cout << "Carry: " << coC << '\n';
		cout << "  Sum: " << sumC << '\n';

		cout << "\n" << "Continue?"; cin >> ai; cout << "\n";

	} while (ai>0);
}
