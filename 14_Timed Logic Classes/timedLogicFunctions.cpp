#include "timedLogicUtilities.h"

/*int main ()
{
wire aW('X', 0), bW('X', 0), ciW('X', 0), coWF('X', 0), sumWF('X', 0),
coWH('X', 0), sumWH('X', 0);

fullAdder *FA = new fullAdder(aW, bW, ciW, coWF, sumWF);
halfAdder *HA = new halfAdder(aW, bW, coWH, sumWH);
int ai;

do {
inpBit("Wire a", aW);
inpBit("Wire b", bW);
inpBit("Wire c", ciW);

FA->evl();
HA->evl();

outBit("FA - Carry", coWF);
outBit("       Sum", sumWF);

outBit("HA - Carry", coWH);
outBit("       Sum", sumWH);

cout << "\n" << "Continue? "; cin >> ai;

} while (ai>0);
}*/

int main ()
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
}

