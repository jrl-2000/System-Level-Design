#include "inheritedLogicClassesUtilities.h"

/*
Jonathan Lopez
Worcester Polytechnic Institute
ECE 5723 Spring 2024
Prof. Z. Navabi

Homework 2:
	RT Level design and C++ logic modeling
Simualtor:
	Microsoft Visual Studio Community 2022
*/


// This is the 2-bit comparator testbench Console Application
int main()
{
	wire a0W('X', 0), a1W('X', 0), b0W('X', 0), b1W('X', 0), lt('X', 0), gt('X', 0), et('X', 0);

	TwoBitComp* TwoBitC = new TwoBitComp(a0W, a1W, b0W, b1W, lt, gt, et);
	int ai = 1;

	do
	{
		inpBit("Input Wire a0", a0W);
		inpBit("Input Wire a1", a1W);
		inpBit("Input Wire b0", b0W);
		inpBit("Input Wire b1", b1W);

		TwoBitC->evl();

		outBit("A < B", lt);
		outBit("A = B", et);
		outBit("A > B", gt);



		cout << "\n" << "Continue? "; cin >> ai;

	} while (ai>0);
}

// This is the 8-bit comparator testbench Console Application
/*int main()
{
	
	wire a0W('X', 0), a1W('X', 0), a2W('X', 0), a3W('X', 0), a4W('X', 0), a5W('X', 0), a6W('X', 0), a7W('X', 0),
		b0W('X', 0), b1W('X', 0), b2W('X', 0), b3W('X', 0), b4W('X', 0), b5W('X', 0), b6W('X', 0), b7W('X', 0),
		lt('X', 0), gt('X', 0), et('X', 0);

	EightBitComp *EightBitC = new EightBitComp(a0W, a1W, a2W, a3W, a4W, a5W, a6W, a7W, b0W, b1W, b2W, b3W, b4W, b5W, b6W, b7W, lt, gt, et);
	int ai=1;

	do {
inpBit("Input Wire a0", a0W);
inpBit("Input Wire a1", a1W);
inpBit("WiInput Wirere a2", a2W);
inpBit("Input Wire a3", a3W);
inpBit("Input Wire a4", a4W);
inpBit("Input Wire a5", a5W);
inpBit("Input Wire a6", a6W);
inpBit("Input Wire a7", a7W);

inpBit("Input Wire b0", b0W);
inpBit("Input Wire b1", b1W);
inpBit("Input Wire b2", b2W);
inpBit("Input Wire b3", b3W);
inpBit("Input Wire b4", b4W);
inpBit("Input Wire b5", b5W);
inpBit("Input Wire b6", b6W);
inpBit("Input Wire b7", b7W);

EightBitC-> evl();

outBit("A < B", lt);
outBit("A = B", et);
outBit("A > B", gt);


		cout << "\n" << "Continue? "; cin >> ai;
		} while (ai>0);
}
*/










// Full Adder and WireV below
/*int main ()
{
	wire A, B;
	wire clk, rst, fb('X',0);
	wire sum, carry;
	
	fullAdder *FA = new fullAdder(A, B, fb, carry, sum);
	dff_ar *FF = new dff_ar(carry, clk, rst, fb, 4, 6);

	int ai=1;

	do {
		inpBit("Serial input A", A);
		inpBit("Serial input B", B);
		inpBit("FF Clock input", clk);
		inpBit("FF Async Reset", rst);

		FA->evl();

		outBit("Carry output ", carry);
		outBit("Serial output", sum);

		FF->evl();

		outBit("Feedback", fb);

		cout << "\n" << "Continue? "; cin >> ai;
		} while (ai>0);

	cout << "Activities: Sum: " << sum.activity()
		<< "; Carry: " << carry.activity()
		<< "; Feedback: " << fb.activity() << '\n';
}*/

/*int main ()
{
	wireV aWV("10101111", 0, 8), bWV("00110000", 0, 8), cWV("00001111", 0, 8),
		wWV("00001111", 0, 8), yWV("XXXX0000", 0, 8);

	andV *AND1 = new andV(aWV, bWV, wWV, 0);
	orV *OR1 = new orV(aWV, bWV, yWV, 0);

	int ai;

	do {
		inpBit("Wire a", aWV);
		inpBit("Wire b", bWV);

		AND1->evl();
		OR1->evl();

		outBit("Wire w AND result", wWV);
		outBit("Wire w  OR result", yWV);

	cout << "\n" << "Continue? "; cin >> ai;

	} while (ai>0);
}*/

