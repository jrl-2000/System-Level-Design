#include "inherited2Primitives.h"
#include "inherited2Functions.h"

void fullAdder (char a, char b, char ci, char & co, char & sum)
{
	char axb, ab, abc;
	XOR* xor1=new XOR;
	XOR* xor2=new XOR;
	AND* and1=new AND;
	AND* and2=new AND;
	OR*  or1 =new OR;

	xor1->inp(a, b); xor1->evl(); xor1->out(axb);
	and1->inp(a, b); and1->evl(); and1->out(ab);
	and2->inp(axb, ci); and2->evl(); and2->out(abc);
	or1->inp(ab, abc); or1->evl(); or1->out(co);
	xor2->inp(axb, ci); xor2->evl(); xor2->out(sum);
}


int main ()
{
	char aC, bC, ciC, coC, sumC;
	char aB;
    int ai;
	
	buf* buf1=new buf;
	buf* buf2=new buf;

	do {

		cout << "Enter a: "; cin >> aC;
		cout << "Enter b: "; cin >> bC;
		cout << "Enter ci: "; cin >> ciC;

		buf1->inp(aC); buf1->evl(); buf1->out(aB);
		cout << "Buff1: " << aB << '\n';
		buf2->inp(aC); buf2->out(aB);
		cout << "Buff2: " << aB << '\n';

		fullAdder (aC, bC, ciC, coC, sumC);
		cout << "Carry: " << coC << ";  Sum: " << sumC << '\n';

		cout << "\n" << "Continue?"; cin >> ai; cout << "\n";

	} while (ai>0);
}
