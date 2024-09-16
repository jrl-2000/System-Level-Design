#include "timedLogicUtilities.h"

void inpBit(string wireName, wire& valtim) {
	char value;
	int time;
	cout << "Enter value followed by @ time for " << wireName << ": ";
	cin >> value; cin >> time; 
	valtim.put(value, time);
}

void outBit(string wireName, wire valtim) {
	char value;
	int time;
	valtim.get(value, time);
	cout << wireName << ": " << value << " @ " << time << "\n";
}