/*
Jonathan Lopez
Worcester Polytechnic Institute
ECE 5723 Spring 2024
Prof. Z. Navabi
Midterm Question # 2:
	C++ Sequence Detector
Synthesizer:
	Microsoft Visual Studio Community 2022
Description:
	Sequence Detector for '10110' Moore State Machine with Overlapping
*/
#include "sequenceDetector.h"


int main ()
{
	int ij;
	bus clk, rst;
	bus a;
	bus w;
	
	sequenceDetector* SD1 = new sequenceDetector(rst, clk, a, w);
	
	// sequenceDetector resetting
	rst = "1";
	SD1->evl();
	rst = "0";

	do{
		for ( int i =0; i<10; i++){
			cout << "\n Enter 1 bits for the input: "; cin >> a;
			clk = "P";
			SD1 -> evl();
			cout << "\n" << w;
		}
		cout << "\n" << "Continue (0 or 1)?"; cin >> ij;
		
	}while (ij >0);
}
