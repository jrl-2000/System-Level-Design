/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*-- Methodologies for System Level Design and Modeling - ECE 5723
/*-- Homework 3: C++ RT-level design and modeling
/*-- by Negin Safari
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include "avgFinder_TOP.h"

int main() {

	int ij = 0;
	int i = 1;

	bus clk, rst, start, ready;
	bus data (8), average (8);

	avgFinder_TOP* UUT = new avgFinder_TOP(rst, clk, start, ready, data, average);

	do {
		i = 1;	
		start = "0";
		rst = "1";
		UUT->eval();
		rst = "0";

		start = "1";
		clk = "P";
		UUT->eval();
		
		start = "0";
		clk = "P";
		cout << "Enter 8 bits for input data " << i << ": "; cin >> data;
		UUT->eval();
		i++;

		do {
			cout << "Enter 8 bits for input data " << i << ": "; cin >> data;
			clk = "P";
			UUT->eval();
			i++;
		} while (i < 9);

		UUT->eval();
		cout << "\n" << "average Input = " << average << "\n";
		cout << "\n" << "Continue (0 or 1)?";
		cin >> ij;
		
	} while (ij > 0);
}