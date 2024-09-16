/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Midterm: Q2. C/C++ RTL Design & Modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "SeqDetector.h"

int main() {

	int ij = 0;
	int i = 0;

	bus clk, rst, a;
	bus w;

	SeqDetector* UUT = new SeqDetector(rst, clk, a, w);

	do {
		i = 1;	
		rst = "1";
		UUT->eval();
		rst = "0";
	
		do {
			cout << "Enter a 1-bit input " << i << ": "; cin >> a;
			clk = "P";
			UUT->eval();
			cout << " w = " << w << endl;
			i++;
		} while (i < 15);

		cout << "\n" << "Continue (0 or 1)?";
		cin >> ij;
		
	} while (ij > 0);
}