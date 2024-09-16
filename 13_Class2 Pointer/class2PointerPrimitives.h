class AND {
	char *i1, *i2, *o1;
	public:
		AND (); // constructor
		~AND(); // destructor
		void ios(char& a, char& b, char &w) { i1 = &a; i2 = &b; o1 = &w; }
		void evl();
};

class OR {
	char *i1, *i2, *o1;
	public:
		OR (); // constructor
		~OR(); // destructor
		void ios(char& a, char& b, char &w) { i1 = &a; i2 = &b; o1 = &w; }
		void evl();
};

class NOT {
	char *i1, *o1;
	public:
		NOT ();
		~NOT(); // destructor
		void ios(char& a, char& w) { i1 = &a; o1 = &w; }
		void evl ();
};

class XOR {
	char *i1, *i2, *o1;
	public:
		XOR ();
		~XOR(); // destructor
		void ios(char& a, char& b, char& w) { i1 = &a; i2 = &b; o1 = &w; }
		void evl();
};

class fullAdder {
	char *i1, *i2, *i3, *o1, *o2;
	public:
		fullAdder (); // constructor
		~fullAdder(); // destructor
		void ios(char& a, char& b, char& ci, char& co, char& sum)
		{
			i1 = &a; i2 = &b; i3 = &ci; o1 = &co; o2 = &sum;
		}
		void evl();
};

class halfAdder {
	char *i1, *i2, *o1, *o2;
	public:
		halfAdder (); // constructor
		~halfAdder(); // destructor
		void ios(char& a, char& b, char& co, char& sum)
		{
			i1 = &a; i2 = &b; o1 = &co; o2 = &sum;
		}
		void evl();
};

