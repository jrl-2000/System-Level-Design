#include "String Character.h"

#define MIN(a,b) ((a<b)?a:b) 

int wave (string seq)
{   int i, l;
	l = seq.length(); 
	for (i=0; i < l; i++)
	{
		if (seq[i]=='0') cout << "__";
		else cout << "--";
	}
	cout << '\n';
	return l;
}

bool char2bool (char c)
{	
	if (c=='0') return 0;
	else return 1;
}

bool operation (string fn, bool in1, bool in2)
{
	bool out;
	if (fn == "AND" || fn == "and") out = in1 && in2;
	else if (fn == "OR" || fn == "or") out = in1 || in2;
	else if (fn == "XOR" || fn == "xor") out = in1 != in2;
	else out = 0;
	return out;
	}

int main ()
{
	string i1Seq, i2Seq;
	string logic; 
	int i, i1Len, i2Len, outLen;
	bool i1=0, i2=0, out=0;
	bool go(1);
	while (go) {
		cout << "Enter logic type and input sequences: ";
		cin >> logic >> i1Seq >> i2Seq; 
		i1Len=wave (i1Seq);
		i2Len=wave (i2Seq);
		outLen = MIN (i1Len, i2Len);
		string outSeq (outLen, '0');
		for (i=0; i<outLen; i++) {
			i1 = char2bool (i1Seq[i]);
			i2 = char2bool (i2Seq[i]);
			out=operation(logic, i1,i2);
			outSeq[i] = out ? '1' : '0';
		}
		outLen=wave (outSeq); cout << '\n';
		cout << "Enter 0 to end:"; cin >> go;
	}
	return 0;
}
