#include "polymorphismLogicClassesUtilities.h"

int main()
{
	wire a('0', 3), b('1', 5), c('X', 0), clk('X', 0), rst('X', 0),
		en('X', 0),
		Q1('X', 0), Q2('X', 0), Q3('X', 0);
	wire v('0', 3), w('0', 3), y('1', 5);

	flipflop *FF1 = new DFF(a, clk, Q1, 401);
	flipflop *FF2 = new DFFsR(a, clk, rst, Q2, 502, 6);
	flipflop *FF3 = new DFFsRE(a, clk, rst, en, Q3, 603, 7);
	FF1->init(float(0.37), '1');
	FF2->init(float(0.37), '1');
	FF3->init(float(0.37), '1');

	gates *NOT1 = new NOT(y, w, 5);
	gates *AND1 = new AND(a, b, v, 7);
	gates *OR1 = new OR(v, c, y, 6);

	AND1->prob();
	OR1->prob();
	NOT1->prob();
	FF1->prob();
	FF2->prob();
	FF3->prob();

	cout << "AND gate Id: " << AND1->gateIdentifier << '\n';
	cout << "OR1 gate Id: " << OR1->gateIdentifier << '\n';
	cout << "NOT gate Id: " << NOT1->gateIdentifier << "\n\n";

	cout << "DFF2 output 1-probability: " << FF2->outputControlability << '\n';
	cout << "DFF3 output 1-probability: " << FF3->outputControlability << "\n\n";

	cout << "AOI  output 1-probability: " << getProb(NOT1) << '\n';
	cout << "DFF1 output 1-probability: " << FF1->outputControlability << '\n';
	cout << "DFF2 output 1-probability: " << FF2->outputControlability << '\n';
	cout << "DFF3 output 1-probability: " << FF3->outputControlability << "\n\n";

	int ai; int time = 0;

	do {
		inpBit("Wire a", a, time);
		inpBit("Wire b", b, time);
		inpBit("Wire c", c, time);
		inpBit("Clock input", clk, time);
		inpBit("Reset input", rst, time);
		inpBit("Enable input", en, time);

		AND1->evl();
		OR1->evl();
		NOT1->evl();

		FF1->evl();
		FF2->evl();
		FF3->evl();

		outBit("AOI  output: ", w);
		outBit("DFF1 output: ", Q1);
		outBit("DFF2 output: ", Q2);
		outBit("DFF3 output: ", Q3);

		cout << "AOI  output activity count: " << w.activity() << '\n';
		cout << "DFF1 output activity count: " << Q1.activity() << '\n';
		cout << "DFF2 output activity count: " << Q2.activity() << '\n';
		cout << "DFF3 output activity count: " << Q3.activity() << "\n\n";

		time += 17;
		cout << "\n" << "Continue? "; cin >> ai; cout << "\n";

	} while (ai>0);
}

/*int main()
{
	wire a('0', 3), b('1', 5), c('X', 0);
	wire v('0', 3), w('0', 3), y('1', 5);

	gates *NOT1 = new NOT(y, w, 5);
	gates *AND1 = new AND(a, b, v, 7);
	gates *OR1 = new OR(v, c, y, 6);

	AND1->prob();
	OR1->prob();
	NOT1->prob();

	int ai; int time = 0;

	do {
		inpBit("Wire a", a, time);
		inpBit("Wire b", b, time);
		inpBit("Wire c", c, time);

		cout << evl(AND) << " :AND\n";
		cout << evl(OR1) << " :OR1\n";
		cout << evl(NOT) << " :NOT\n";

		outBit("AOI  output: ", w);
		cout << "AOI  output activity count: " << w.activity() << '\n';

		time += 17;
		cout << "\n" << "Continue? "; cin >> ai; cout << "\n";
	} while (ai>0);
}*/



/*int main()
{
	wire aW('0', 3), bW('1', 5), ciW('X', 0), coWF('X', 0), sumWF('X', 0),
		coWH('X', 0), sumWH('X', 0);
	wire dW('X', 4), eW('X', 4);
	wire fW('X', 4), gW('X', 4);

	fullAdder *FA = new fullAdder(aW, bW, ciW, coWF, sumWF);
	halfAdder *HA = new halfAdder(aW, bW, coWH, sumWH);
	//not *NOT = new NOT(aW, dW, 5); // or use gates as below
	gates *NOT1 = new NOT(aW, dW, 5); // "not" can do everything that "gates" can.
	gates *AND1 = new AND(aW, bW, eW, 7); // this uses and::evl() 
	                                     // because gates::evl() is virtual, if not
	                                     // it would use gates::evl()
	gates *OR1 = new OR(eW, ciW, gW, 6);

	AND1->prob();
	OR1->prob();
	FA->prob();
	
	cout << "AND-OR output: " << getProb(OR1) << '\n';

	cout << "Fulladder output1: " << FA->o1Controlability << '\n';
	cout << "Fulladder output2: " << FA->o2Controlability << "\n\n";

	int ai;

	do {
		inpBit("Wire a", aW);
		inpBit("Wire b", bW);
		inpBit("Wire c", ciW);

		FA->evl();
		HA->evl();
		NOT1->evl();
		AND1->evl();
		OR1->evl();

		outBit("FA - Carry", coWF);
		outBit("       Sum", sumWF);

		outBit("HA - Carry", coWH);
		outBit("       Sum", sumWH);

		outBit("NOT - Gate", dW);
		outBit("AND - Gate", eW);
		outBit("AO  - Gate", gW);

		cout << "\n" << "Continue? "; cin >> ai;

	} while (ai>0);
}
*/
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

	andV *AND = new andV(aWV, bWV, wWV, 0);
	orV *OR = new orV(aWV, bWV, yWV, 0);

	int ai;

	do {
		inpBit("Wire a", aWV);
		inpBit("Wire b", bWV);

		AND->evl();
		OR->evl();

		outBit("Wire w AND result", wWV);
		outBit("Wire w  OR result", yWV);

	cout << "\n" << "Continue? "; cin >> ai;

	} while (ai>0);
}*/

