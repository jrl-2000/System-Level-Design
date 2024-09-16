#include "polymorphismLogicClassesFunctions.h"

class wire {
protected:
	static int numberOfWires;
public:
	char value;
	int eventTime;
	int activityCount = 0;
	float controlability = 0.5;
public:
	int wireIdentifier;	
	wire(char c, int d) : value(c), eventTime(d) {
		wireIdentifier = numberOfWires;
		numberOfWires++;
	}
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

	void timingActivity2();
	void timingActivity1();
	static int numberOfGates;
public:
	int gateIdentifier;
	float outputControlability = 1.0; 
	gates(wire& a, wire& w, int d) : 
		i1(&a), o1(&w), gateDelay(d) {
		gateIdentifier = numberOfGates;
		numberOfGates++;
	}
	gates(wire& a, wire& b, wire& w, int d) : 
		i1(&a), i2(&b), o1(&w), gateDelay(d) {
		gateIdentifier = numberOfGates;
		numberOfGates++;
	}
	gates(){};
	~gates(){};
	virtual void evl();
	virtual void prob(){};
};

float getProb(gates*);
float evl(gates*);

class AND: public gates {
public:
	AND(wire& a, wire& b, wire& w, int d) : gates(a, b, w, d) {}
	~AND();
	void evl();
	void prob();
};

class OR: public gates {
public:
	OR(wire& a, wire& b, wire& w, int d) : gates(a, b, w, d) {}
	~OR();
	void evl();
	void prob();
};

class NOT: public gates {
public:
	NOT(wire& a, wire& w, int d) : gates(a, w, d) {}
	~NOT();
	void evl();
	void prob();
};

class XOR: public gates {
public:
	XOR(wire& a, wire& b, wire& w, int d) : gates(a, b, w, d) {}
	~XOR();
	void evl();
	void prob();
};

class flipflop {
protected:
	wire *D, *clk, *rst, *cen, *Q;
	int clkQDelay;
	int rstQDelay;
	int lastEvent; // last time output changed
	char lastValue;
	bool containsReset = false;
	float clockControlability = 0.5;
	static int numberOfFlipflops; 
public:
	int flipflopIdentifier;
	float outputControlability = 1.0;
	flipflop(wire& d, wire& c, wire& q, int dC) :
		D(&d), clk(&c), Q(&q), clkQDelay(dC) {
		flipflopIdentifier = numberOfFlipflops;
		numberOfFlipflops++;
	};
	~flipflop(){};
	virtual void evl() = 0;
	virtual void prob() = 0;
	virtual void init(float, char) = 0;
};

class DFF : public flipflop {
public:
	DFF(wire& d, wire& c, wire& q, int dC) : flipflop(d, c, q, dC) 
	{ containsReset = false; };
	~DFF(){};
	virtual void evl();
	virtual void prob();
	virtual void init(float, char);
};

class DFFsR : public DFF {
public:
	DFFsR(wire& d, wire& c, wire& r, wire& q, int dC, int dR) : DFF(d, c, q, dC) {
		containsReset = true;
		rst = &r;
		rstQDelay = dR;
	};
	~DFFsR(){};
	virtual void prob();
};

class DFFsRE : public DFFsR {
public:
	DFFsRE(wire& d, wire& c, wire& r, wire& e, 
		wire& q, int dC, int dR) : DFFsR(d, c, r, q, dC, dR) {
		cen = &e;
	};
	~DFFsRE(){};
	virtual void evl();
};


// Structures based on above primitives begin here

class fullAdder {
	wire *i1, *i2, *i3, *o1, *o2;

	// Declare necessary gate instances
	gates *xor1;
	gates *xor2;
	gates *and1;
	gates *and2;
	gates  *or1;


	
	// fulladder Local wires
	wire aL, bL, ciL;
	wire coL, sumL;
	wire axbL, abL, abcL;

public:
	float o1Controlability, o2Controlability;
	
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
		void prob();
};

class halfAdder {
	wire *i1, *i2, *o1, *o2;

	// Declare necessary gate instances
	gates *xor1;
	gates *and1;

	float o1Controlability, o2Controlability;

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
		void prob();
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

