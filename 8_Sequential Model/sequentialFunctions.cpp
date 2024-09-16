#include "characterPrimitives.h"
#include "sequentialFunctions.h"

int main ()
{
	string inVec;
	string outVec = ",,,,";
	char ain('0'), reset, clock;

	char Y1('X'), Y0('X'), D1, D0, w;

	ifstream finp ( "indata.tst");
	ofstream fout ("outdata.tst");

	fout << "Inp -> Output, Next state\n";
	
	do {
		finp >> inVec;
			ain = inVec[0];
			reset = inVec[1];
			clock = inVec[2];
		// combinational parts in proceduaral fashion
		// followed by the sequential parts

		D1 = OR(AND(Y1, Y0), AND (ain, Y0));
		D0 = ain;
		w = AND(Y1, NOT(Y0));

		outVec[0] = w;  // These values are after
		outVec[2] = Y1; //   application of the 
		outVec[3] = Y0; //   previous inputs
		fout << outVec+"\n" << inVec << " -> ";
		
		dff_PAH (D1, clock, reset, Y1);
		dff_PAH (D0, clock, reset, Y0);
	} while (!finp.eof());
}
