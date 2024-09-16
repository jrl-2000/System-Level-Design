#include "logicGates.h"
#include "primitives.h"

void fullAdder (bool a, bool b, bool ci, bool& co, bool& sum)
{
	bool axb, ab, abc;

	axb = XOR (a, b);
	ab  = AND (a, b);
	abc = AND (axb, ci);
	co = OR (ab, abc);
	sum = XOR (axb, ci);
}

/*
void fullAdder (bool a, bool b, bool ci, bool& co, bool& sum)
{
	bool axb, ab, abc;

	XOR (a, b, axb);
	AND (a, b, ab);
	AND (axb, ci, abc);
	OR (ab, abc, co);
	XOR (axb, ci, sum);
}
*/

/*
void fullAdder (bool a, bool b, bool ci, bool& co, bool& sum)
{
	bool axb, ab, abc;

	axb = logic (a, b, XOR); // uses: void XOR (bool, bool, bool&);
	ab  = logic (a, b, AND);
	abc = logic (axb, ci, AND);
	co  = logic (ab, abc, OR);
	sum = logic (axb, ci, XOR);
}
*/

/*
void fullAdder (bool a, bool b, bool ci, bool& co, bool& sum)
{
	bool ab, bc, ac;

	ab = AND5 (a, b);
	bc = AND5 (b, ci);
	ac = AND5 (a, ci);
	co = OR5 (ab, bc, ac);
	sum = XOR5 (a, b, ci);
}
*/

int main ()
{
	bool a, b, c, co, sum;

	do {
		cout << "Enter a, b, c: "; cin >> a >> b >> c;

		fullAdder (a, b, c, co, sum);

		cout << "Carry:" << co << " Sum:" << sum << "\n";

		cout << "\n" << "Continue?"; cin >> a;
	} while (a != false);
}

