// --- WPI --- Object Oriented Design --- HW2
// --- Solution by: Negin Safari

#pragma once
#include <iostream>
#include <string>
using namespace std;
//----------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------Using Provided Library--------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
class wire {
public:
	char value;
	int eventTime;
	int activityCount;
public:
	wire(char c, int d) : value(c), eventTime(d) {}
	wire(){};
	void put(char a, int d) { value = a; eventTime = d; }
	void get(char& a, int& d) { a = value; d = eventTime; }
	int activity() { return activityCount; }
};

class gates {
protected:
	wire *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char lastValue;
public:
	gates(wire& a, wire& w, int d) : 
		i1(&a), o1(&w), gateDelay(d) {}
	gates(wire& a, wire& b, wire& w, int d) : 
		i1(&a), i2(&b), o1(&w), gateDelay(d) {}
	gates(){};
	~gates(){};
	void evl();
	void timingActivity2();
	void timingActivity1();
};

class AND: public gates {
public:
	AND(wire& a, wire& b, wire& w, int d) : gates(a, b, w, d) {}
	~AND();
	void evl();
};

class OR: public gates {
public:
	OR(wire& a, wire& b, wire& w, int d) : gates(a, b, w, d) {}
	~OR();
	void evl();
};

class NOT: public gates {
public:
	NOT(wire& a, wire& w, int d) : gates(a, w, d) {}
	~NOT();
	// void evl() does not exist, will use gates::evl()
};

class XOR: public gates {
public:
	XOR(wire& a, wire& b, wire& w, int d) : gates(a, b, w, d) {}
	~XOR();
	void evl();
};

class wireV {
public:
	char* value;
	int n; //Bits
	int eventTime;
	int activityCount;
public:
	wireV(string v, int d, int size);
	wireV(){};
	~wireV(){};
	void put(string a, int d);
	void get(string& a, int& d);
	int activity() { return activityCount; }
};

void inpBit(string, wire&);
void outBit(string, wire);

void inpBit(string, wireV&);
void outBit(string, wireV);

//----------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------- 2-bit cascadable comparator --------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
class Comparator_2bit { 
	wire *A1, *A0, *B1, *B0, *eqIn, *gtIn, *ltIn;
	wire *eqOut, *gtOut, *ltOut; 
	
	// Declare necessary gate instances
	XOR *xor1;
	XOR *xor2;
	XOR *xor3;
	NOT *not1;
	NOT *not2;
	NOT *not3;
	NOT *not4;
	NOT *not5;
	NOT *not6;
	AND *and1;
	AND *and2;
	AND *and3;
	AND *and4;
	AND *and5;
	OR  *or1;
	OR  *or2;
	OR  *or3;
	OR  *or4;
	OR  *or5;

	// Local wires
	wire A1L, A0L, B1L, B0L, eqInL, gtInL, ltInL;
	wire not1_Out, not2_Out, not3_Out, not4_Out, not5_Out, not6_Out;
	wire and1_Out, and2_Out, and3_Out, and4_Out, and5_Out;
	wire xor1_Out, xor2_Out, xor3_Out;
	wire or1_Out, or2_Out, or3_Out;
	wire eqOutL, gtOutL, ltOutL;

  public: 
	Comparator_2bit(wire& _A1, wire& _A0, wire& _B1, wire& _B0, wire& _eqIn, wire& _gtIn, wire& _ltIn, wire& _eqOut, wire& _gtOut, wire& _ltOut) :
		A1(&_A1), A0(&_A0), B1(&_B1), B0(&_B0), eqIn(&_eqIn), gtIn(&_gtIn), ltIn(&_ltIn), eqOut(&_eqOut), gtOut(&_gtOut), ltOut(&_ltOut),
		A1L('X', 0), A0L('X', 0), B1L('X', 0), B0L('X', 0), eqInL('X', 0), gtInL('X', 0), ltInL('X', 0),
		not1_Out('X', 0), not2_Out('X', 0), not3_Out('X', 0), not4_Out('X', 0), not5_Out('X', 0), not6_Out('X', 0),
		and1_Out('X', 0), and2_Out('X', 0), and3_Out('X', 0), and4_Out('X', 0), and5_Out('X', 0),
		xor1_Out('X', 0), xor2_Out('X', 0), xor3_Out('X', 0),
		or1_Out('X', 0), or2_Out('X', 0), or3_Out('X', 0),
		eqOutL('X', 0), gtOutL('X', 0), ltOutL('X', 0) {

		// Associate ports of the gates with the Local wires
		xor1 = new XOR(A1L, B1L, xor1_Out, 0); 
		xor2 = new XOR(A0L, B0L, xor2_Out, 0); 
		not1 = new NOT(xor1_Out, not1_Out, 0);
		and1 = new AND(xor2_Out, B0L, and1_Out, 0);
		not2 = new NOT(and1_Out, not2_Out, 0);
		or1  = new OR (B1L, not1_Out, or1_Out, 0);
		and2 = new AND(not1_Out, not2_Out, and2_Out, 0);
		not3 = new NOT(or1_Out, not3_Out, 0);
		not4 = new NOT(and2_Out, not4_Out, 0);
		xor3 = new XOR(not3_Out, not4_Out, xor3_Out, 0); 
		or2  = new OR (xor2_Out, not4_Out, or2_Out, 0);
		not5 = new NOT(or2_Out, not5_Out, 0);
		or3  = new OR (xor3_Out, not5_Out, or3_Out, 0);
		not6 = new NOT(or3_Out, not6_Out, 0);
		and3 = new AND(eqInL, xor3_Out, and3_Out, 0);
		and4 = new AND(eqInL, not6_Out, and4_Out, 0);
		and5 = new AND(eqInL, not5_Out, eqOutL, 0);
		or4  = new OR (ltInL, and3_Out, ltOutL, 0);
		or5  = new OR (gtInL, and4_Out, gtOutL, 0);
		
	};
		
	~Comparator_2bit() {}; 
	void evl();
};

//----------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------- 8-bit cascadable comparator --------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
class Comparator_8bit { 
	wireV *A, *B; 
	wire *eqIn, *gtIn, *ltIn;
	wire *eqOut, *gtOut, *ltOut; 
	
	// Declare necessary gate instances
	Comparator_2bit *comp[4];

	// Local wires
	wire AL[8], BL[8];
	wire eqOutL[5], gtOutL[5], ltOutL[5];

  public: 
	Comparator_8bit(wireV& _A, wireV& _B, wire& _eqIn, wire& _gtIn, wire& _ltIn, wire& _eqOut, wire& _gtOut, wire& _ltOut) :
		A(&_A), B(&_B), eqIn(&_eqIn), gtIn(&_gtIn), ltIn(&_ltIn), eqOut(&_eqOut), gtOut(&_gtOut), ltOut(&_ltOut) {

		// Associate ports of the gates with the Local wires
		for (int i = 3; i >= 0; i--) {
			comp[i] = new Comparator_2bit(AL[2*i+1], AL[2*i], BL[2*i+1], BL[2*i], eqOutL[i+1], gtOutL[i+1], ltOutL[i+1], eqOutL[i], gtOutL[i], ltOutL[i]); 
		}
	};
		
	~Comparator_8bit() {}; 
	void evl();
};





/////////////////////////////////////////////////////////////////////////////////


#define MAX(a,b) ((a>b)?a:b)

int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int in2LastEvent, int gateDelay, int lastEvent){

	if (lastValue == newValue) 
		return lastEvent;
	else 
		return gateDelay + MAX (in1LastEvent, in2LastEvent);
}

int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int gateDelay, int lastEvent){

	if (lastValue == newValue) 
		return lastEvent;
	else 
		return gateDelay + in1LastEvent;
}

void gates::evl() { // inverts its input 1

	if (i1->value == '0')
		o1->value = '1';
	else if (i1->value == '1')
		o1->value = '0';
	else
		o1->value = 'X';

	gates::timingActivity1();
}
void gates::timingActivity2() {

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, i2->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + i2->activityCount +
		((lastValue == o1->value) ? 0 : 1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}
void gates::timingActivity1() {

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + ((lastValue == o1->value)?0:1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}

void AND::evl() {

	if ((i1->value == '0') || (i2->value == '0'))
		o1->value = '0';
	else if ((i1->value == '1') && (i2->value == '1'))
		o1->value = '1';
	else
		o1->value = 'X';

	gates::timingActivity2();
}

void OR::evl() {

	if ((i1->value == '1') || (i2->value == '1')) 
		o1->value = '1';
	else if ((i1->value=='0')&&(i2->value=='0')) 
		o1->value='0';
	else 
		o1->value='X';

	gates::timingActivity2();
}

void XOR::evl () {

	if ((i1->value == 'X') || (i2->value == 'X') ||
		(i1->value == 'Z') || (i2->value == 'Z')) 
		o1->value = 'X';
	else if (i1->value==i2->value) 
		o1->value='0';
	else 
		o1->value='1';

	gates::timingActivity2();
}

wireV::wireV(string v, int d, int size) : eventTime(d), n(size) {
	int i;
	value = new char[n + 1];
	v.resize(n, 'X');
	for (i = 0; i < n; i++){ *(i + value) = v.at(i); };
	*(n + value) = '\0';
}
void wireV::put(string a, int d){
	int i;
	eventTime = d;
	a.resize(n, '0');
	for (i = 0; i < n; i++){ *(i + value) = a.at(i);};
}
void wireV::get(string& a, int& d){
	int i;
	d = eventTime;
	a.resize(n, '0');
	for (i = 0; i < n; i++){ a.at(i) = *(i + value); };
}

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

void inpBit(string wireName, wireV& valtim) {
	string value;
	int time;
	cout << "Enter value followed by @ time for " << wireName << ": ";
	cin >> value; cin >> time;
	valtim.put(value, time);
}

void outBit(string wireName, wireV valtim) {
	string value;
	int time;
	valtim.get(value, time);
	cout << wireName << ": " << value << " @ " << time << "\n";
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------- 2-bit cascadable comparator --------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
void Comparator_2bit::evl () {
    
	
	A1L = *A1; A0L = *A0; B1L = *B1; B0L = *B0; eqInL = *eqIn; gtInL = *gtIn, ltInL = *ltIn;
    
	xor1->evl();
    xor2->evl();
    not1->evl();
    and1->evl();
    not2->evl();
    or1 ->evl();
    and2->evl();
    not3->evl();
    not4->evl();
    xor3->evl();
    or2 ->evl();
    not5->evl();
    or3 ->evl();
    not6->evl();
    and3->evl();
    and4->evl();
    and5->evl();
    or4 ->evl();
    or5 ->evl();

	*eqOut = eqOutL; *ltOut = ltOutL; *gtOut = gtOutL;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------- 8-bit cascadable comparator --------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
void Comparator_8bit::evl () {
	
	eqOutL[4] = *eqIn;
	gtOutL[4] = *gtIn;
	ltOutL[4] = *ltIn;
	
	for (int i = 3; i >= 0; i--) {
		AL[2*i+1].value = A->value[7 - (2*i+1)];
		BL[2*i+1].value = B->value[7 - (2*i+1)];
		AL[2*i].value = A->value[7 - (2*i)];
		BL[2*i].value = B->value[7 - (2*i)];
		comp[i]->evl();
// 		cout<<"eq: "<<i<<"  "<<eqOutL[i].value<<endl;
// 		cout<<"gt: "<<i<<"  "<<gtOutL[i].value<<endl;
// 		cout<<"lt: "<<i<<"  "<<ltOutL[i].value<<endl;
	}
	
	*eqOut = eqOutL[0]; 
	*gtOut = gtOutL[0];
	*ltOut = ltOutL[0];
}




/////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------- Testbench for 1-bit comparator --------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
// int main() {
	
// 	wire A1('0', 0);
// 	wire A0('0', 0);
// 	wire B1('0', 0);
// 	wire B0('0', 0);
// 	wire eqIn('1', 0);
// 	wire gtIn('0', 0);
// 	wire ltIn('0', 0);
	
// 	wire eqOut('X', 0);
// 	wire gtOut('X', 0);
// 	wire ltOut('X', 0);
	
// 	Comparator_2bit *compUT = new Comparator_2bit(A1, A0, B1, B0, eqIn, gtIn, ltIn, eqOut, gtOut, ltOut);

// 	int ai = 0;
// 	cout << " ****** 2-bit Comparator ****** " << endl; 
// 	do {
// 		inpBit("A[1] Input - 1bit ", A1);
// 		inpBit("A[0] Input - 1bit ", A0);
// 		inpBit("B[1] Input - 1bit ", B1);
// 		inpBit("B[0] Input - 1bit ", B0);
		
// 		compUT->evl();
		
// 		cout << "eqOut= " << eqOut.value << endl;
// 		cout << "gtOut= " << gtOut.value << endl;
// 		cout << "ltOut= " << ltOut.value << endl;
// 		cout << "---------------------------------" << endl;
		
// 		ai++;
// 	} while (ai<10);
// }



//----------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------- Testbench for 8-bit comparator --------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
int main() {
	
	wireV A("00000000", 0, 8);
	wireV B("00000000", 0, 8);
	wire eqIn('1', 0);
	wire gtIn('0', 0);
	wire ltIn('0', 0);
	
	wire eqOut('X', 0);
	wire gtOut('X', 0);
	wire ltOut('X', 0);
	
	Comparator_8bit *compUT = new Comparator_8bit(A, B, eqIn, gtIn, ltIn, eqOut, gtOut, ltOut);

	int ai = 0;
	cout << " ****** 8-bit Comparator ****** " << endl; 
	do {
		inpBit("A Input - 8bit ", A);
		inpBit("B Input - 8bit ", B);
		compUT->evl();
		cout << "eqOut= " << eqOut.value << endl;
		cout << "gtOut= " << gtOut.value << endl;
		cout << "ltOut= " << ltOut.value << endl;
		cout << "---------------------------------" << endl;
		
		ai++;
	} while (ai<10);
}
