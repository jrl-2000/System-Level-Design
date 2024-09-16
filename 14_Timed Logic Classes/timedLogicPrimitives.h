int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int in2LastEvent, int gateDelay, int lastEvent);

class wire {
public:
	char value;
	int eventTime;
	int activityCount=0;
	public:
		wire(char c, int d) : value(c), eventTime(d) {}
		wire(){};
		void put(char a, int d) { value = a; eventTime = d; }
		void get(char& a, int& d) { a = value; d = eventTime; }
		int activity() { return activityCount; }
}; 

class AND {
	wire *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char lastValue;
	public:
		AND(wire& a, wire& b, wire& w, int d) :
			i1(&a), i2(&b), o1(&w), gateDelay(d) {};
		~AND(); 
		void evl();
};

class OR {
	wire *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char lastValue;
	public:
		OR(wire& a, wire& b, wire& w, int d) : i1(&a), i2(&b), o1(&w), gateDelay(d) {};
		~OR(); 
		void evl();
};

class NOT {
	wire *i1, *o1;
	int gateDelay, lastEvent;
	char lastValue;
	public:
		NOT(wire& a, wire& w, int d) : i1(&a), o1(&w), gateDelay(d) {};
		~NOT(); 
		void evl ();
};

class XOR {
	wire *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char lastValue = 'X';
	public:
		XOR(wire& a, wire& b, wire& w, int d) : i1(&a), i2(&b), o1(&w), gateDelay(d) {};
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

