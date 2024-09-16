#include "inheritedLogicClassesFunctions.h"

class wire {
public:
	char value;
	int eventTime;
	int activityCount = 0;
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

class dff_ar {
	wire *D, *clk, *R, *Q;
	int clkQDelay, rstQDelay;
	int lastEvent; // last time output changed
	char lastValue;

	public:
		dff_ar(wire& d, wire& c, wire& r, wire& q, int dC, int dR) :
			D(&d), clk(&c), R(&r), Q(&q), clkQDelay(dC), rstQDelay(dR) {};
		~dff_ar();
		void evl();
};

// Structures based on above primitives begin here

class TwoBitComp {
	wire* ia0, * ia1, * ib0, * ib1, * oL, * oG, * oE;
	// Declare necessary gate instances
	// To NOT all inputs
	NOT* not1;
	NOT* not2;
	NOT* not3;
	NOT* not4;

	// Equal
	XOR* xor1;
	XOR* xor2;
	NOT* not5;
	NOT* not6;
	AND* and1;

	// Greater Than___________________
	// A1B1’ 
	AND* and2;
	//AND* and3;

	// A0B1’B0’
	AND* and4;
	AND* and5;
	//AND* and6;

	// A1A0B0’
	AND* and7;
	AND* and8;


	// Eval O/P of AND gates
	OR* or1;
	OR* or2;



	// Less Than___________________
	// A1’B1
	AND* and9;


	//A0’B1B0
	AND* and10;
	AND* and11;

	// A1’A0’B0
	AND* and12;
	AND* and13;

	// Eval O/P of AND gates
	OR* or3;
	OR* or4;

	wire a0l, a1l, b0l, b1l;
	wire na0, na1, nb0, nb1;

	// Equal
	wire A0_XOR_B0, A1_XOR_B1;
	wire N_A0_XOR_B0, N_A1_XOR_B1; // XNOR

	// Greater Than
	wire A1_NB1, A0_NB1, A0_NB1_NB0, A0_A1, A0_A1_nB0;
	wire OR_A0_A1_nB0_A0_NB1_NB0;

	// Less than
	wire nA1_B1, nA0_B1, nA0_B1_B0, nA1_nA0, nA1_nA0_B0;
	wire OR_nA0_B1_B0_nA1_nA0_B0;

	// Output
	wire lt, gt, et;

public:
	TwoBitComp(wire& a0, wire& a1, wire& b0, wire& b1, wire& L, wire& G, wire& E) :
		ia0(&a0), ia1(&a1), ib0(&b0), ib1(&b1), oL(&L), oG(&G), oE(&E) {

		// Associate ports of the gates with the Local FA wires
		// Equal To
		not1 = new NOT(a0l, na0, 0);
		not2 = new NOT(a1l, na1, 0);
		not3 = new NOT(b0l, nb0, 0);
		not4 = new NOT(b1l, nb1, 0);


		// Equal To
		xor1 = new XOR(a0l, b0l, A0_XOR_B0, 0);
		xor2 = new XOR(a1l, b1l, A1_XOR_B1, 0);

		not5 = new NOT(A0_XOR_B0, N_A0_XOR_B0, 0);
		not6 = new NOT(A1_XOR_B1, N_A1_XOR_B1, 0);

		and1 = new AND(N_A0_XOR_B0, N_A1_XOR_B1, et, 0);

		// Greater Than
		and2 = new AND(a1l, nb1, A1_NB1, 0);

		and4 = new AND(a0l, nb1, A0_NB1, 0);
		and5 = new AND(A0_NB1, nb0, A0_NB1_NB0, 0);

		and7 = new AND(a0l, a1l, A0_A1, 0);
		and8 = new AND(A0_A1, nb0, A0_A1_nB0, 0);

		or1 = new OR(A0_A1_nB0, A0_NB1_NB0, OR_A0_A1_nB0_A0_NB1_NB0, 0);
		or2 = new OR(OR_A0_A1_nB0_A0_NB1_NB0, A1_NB1, gt, 0);

		// Less Than
		and9 = new AND(na1, b1l, nA1_B1, 0);

		and10 = new AND(na0, b1l, nA0_B1, 0);
		and11 = new AND(nA0_B1, b0l, nA0_B1_B0, 0);

		and12 = new AND(na1, na0, nA1_nA0, 0);
		and13 = new AND(nA1_nA0, b0l, nA1_nA0_B0, 0);

		or3 = new OR(nA0_B1_B0, nA1_nA0_B0, OR_nA0_B1_B0_nA1_nA0_B0, 0);
		or4 = new OR(nA1_B1, OR_nA0_B1_B0_nA1_nA0_B0, lt, 0);
	};
	~TwoBitComp();
	void evl();
};


class EightBitComp {
	wire* ia0, * ia1, * ia2, * ia3, * ia4, * ia5, * ia6, * ia7, * ib0, * ib1, * ib2, * ib3, * ib4, * ib5, * ib6, * ib7, * oL, * oG, * oE;

	// Declare necessary gate instances
	TwoBitComp* TwoBitCompHigh0; 
	TwoBitComp* TwoBitCompHigh1;
	TwoBitComp* TwoBitCompLow2;
	TwoBitComp* TwoBitCompLow3;

	// Equal to
	AND* and1;
	AND* and2;
	AND* and3;

	// Upper
	AND* and4;
	AND* and5;

	OR* or1;
	OR* or2;


	// Lower

	AND* and6;
	AND* and7;

	OR* or3;
	OR* or4;

	// Last few
	AND* and8;
	OR* or5;
	AND* and9;
	OR* or6;


	// Local Wires
	// Equal To
	wire ETH;
	wire ETL;


	// Upper
	wire LT1_ET0;
	wire GT1_ET0;

	wire LT0_OR_LT1_ET0; // LTH
	wire GT0_OR_GT1_ET0; // GTH

	// Lower
	wire LT3_ET2;
	wire GT3_ET2;

	wire LT2_OR_LT3_ET2; // LTL
	wire GT2_OR_GT3_ET2; // GTL

	// 4-bits to 8-bits gates
	// Less Than
	wire AND_ETH_LT2_OR_LT3_ET2;
	
	// Greater Than
	wire AND_ETH_GT2_OR_GT3_ET2;


	// Other Wires
	// Local wires
	wire a0L, a1L, a2L, a3L, a4L, a5L, a6L, a7L;
	wire b0L, b1L, b2L, b3L, b4L, b5L, b6L, b7L;
	wire LT0, GT0, ET0;
	wire LT1, GT1, ET1;
	wire LT2, GT2, ET2;
	wire LT3, GT3, ET3;
	wire LT, GT, ET;
public:
	EightBitComp(wire& a0, wire& a1, wire& a2, wire& a3, wire& a4, wire& a5, wire& a6, wire& a7,
		wire& b0, wire& b1, wire& b2, wire& b3, wire& b4, wire& b5, wire& b6, wire& b7,
		wire& lt, wire& gt, wire& e) :
		ia0(&a0), ia1(&a1), ia2(&a2), ia3(&a3), ia4(&a4), ia5(&a5), ia6(&a6), ia7(&a7),
		ib0(&b0), ib1(&b1), ib2(&b2), ib3(&b3), ib4(&b4), ib5(&b5), ib6(&b6), ib7(&b7),
		oL(&lt), oG(&gt), oE(&e) {

		// Associate ports of the gates with the Local FA wires
		TwoBitCompHigh0 = new TwoBitComp(a6L, a7L, b6L, b7L, LT0, GT0, ET0);
		TwoBitCompHigh1 = new TwoBitComp(a4L, a5L, b4L, b5L, LT1, GT1, ET1);
		TwoBitCompLow2 = new TwoBitComp(a2L, a3L, b2L, b3L, LT2, GT2, ET2);
		TwoBitCompLow3 = new TwoBitComp(a0L, a1L, b0L, b1L, LT3, GT3, ET3);


		// Gates

		// Equal To
		and1 = new AND(ET0, ET1, ETH, 0);
		and2 = new AND(ET2, ET3, ETL, 0);
		and3 = new AND(ETH, ETL, ET, 0);

		// Upper
		and4 = new AND(LT1, ET0, LT1_ET0, 0);
		and5 = new AND(GT1, ET0, GT1_ET0, 0);

		or1 = new OR(LT0, LT1_ET0, LT0_OR_LT1_ET0, 0); // LTH
		or2 = new OR(GT0, GT1_ET0, GT0_OR_GT1_ET0, 0); // GTH

		// Lower
		and6 = new AND(LT3, ET2, LT3_ET2, 0);
		and7 = new AND(GT3, ET2, GT3_ET2, 0);

		or3 = new OR(LT2, LT3_ET2, LT2_OR_LT3_ET2, 0); // LTL
		or4 = new OR(GT2, GT3_ET2, GT2_OR_GT3_ET2, 0); // GTL

		// Last Few
		and8 = new AND(LT2_OR_LT3_ET2, ETH, AND_ETH_LT2_OR_LT3_ET2, 0);
		or5 = new OR(LT0_OR_LT1_ET0, AND_ETH_LT2_OR_LT3_ET2, LT, 0); // Less Than
		and9 = new AND(GT2_OR_GT3_ET2, ETH, AND_ETH_GT2_OR_GT3_ET2, 0);
		or6 = new OR(GT0_OR_GT1_ET0, AND_ETH_GT2_OR_GT3_ET2, GT, 0); // Greater Than
	};
	~EightBitComp();
	void evl();
};

class fullAdder {
	wire *i1, *i2, *i3, *o1, *o2;

	// Declare necessary gate instances
	XOR *xor1;
	XOR *xor2;
	AND *and1;
	AND *and2;
	OR  *or1;

	// fulladder Local wires
	wire aL, bL, ciL;
	wire coL, sumL;
	wire axbL, abL, abcL;

	public:
		fullAdder(wire& a, wire& b, wire& ci, wire& co, wire& sum) :
			i1(&a), i2(&b), i3(&ci), o1(&co), o2(&sum),  
			aL('X', 0), bL('X', 0), ciL('X', 0),
			coL('X', 0), sumL('X', 0), 
			axbL('X', 0), abL('X', 0), abcL('X', 0) {

		// Associate ports of the gates with the Local FA wires
		xor1 = new XOR(aL, bL, axbL, 5); // 5 is gate delay
		xor2 = new XOR(axbL, ciL, sumL, 5);
		and1 = new AND(aL, bL, abL, 3);
		and2 = new AND(axbL, ciL, abcL, 3);
		or1 = new OR(abL, abcL, coL, 3);
		};
		~fullAdder(); 
		void evl();
};

class halfAdder {
	wire *i1, *i2, *o1, *o2;

	// Declare necessary gate instances
	XOR *xor1;
	AND *and1;

	// halfadder Local wires
	wire aL, bL;
	wire coL, sumL;

	public:
		halfAdder(wire& a, wire& b, wire& co, wire& sum) :
			i1(&a), i2(&b), o1(&co), o2(&sum), 
			aL('X', 0), bL('X', 0), coL('X', 0), sumL('X', 0){
			
		// Associate ports of the gates with the Local HA wires
		xor1 = new XOR(aL, bL, sumL, 5);
		and1 = new AND(aL, bL, coL, 3);

		};
		~halfAdder(); 
		void evl();
};

// -----------------Vector Logic---------------- //

class wireV {
public:
	char* value;
	int n; //Bits
	int eventTime;
	int activityCount = 0;
public:
	wireV(string v, int d, int size);
	wireV(){};
	~wireV(){};
	void put(string a, int d);
	void get(string& a, int& d);
	int activity() { return activityCount; }
};

class andV {
	wireV *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char* lastValue;
public:
	andV(wireV& a, wireV& b, wireV& w, int d) :
		i1(&a), i2(&b), o1(&w), gateDelay(d) {
		lastValue = new char[w.n+1];
	};
	~andV(){};
	void evl();
};

class orV {
	wireV *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char* lastValue;
public:
	orV(wireV& a, wireV& b, wireV& w, int d) :
		i1(&a), i2(&b), o1(&w), gateDelay(d) {
		lastValue = new char[w.n + 1];
	};
	~orV(){};
	void evl();
};

