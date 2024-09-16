class AND {
	char i1, i2, o1;
	public:
		AND (); // constructor
		void inp (char a, char b) {i1=a; i2=b;}
		void evl ();
		void out (char& w) {w=o1;}
};

class OR {
	char i1, i2, o1;
	public:
		OR (); // constructor
		void inp (char a, char b) {i1=a; i2=b;}
		void evl ();
		void out (char& w) {w=o1;}
};

class NOT {
	char i1, o1;
	public:
		NOT ();
		void inp (char a) {i1=a;}
		void evl ();
		void out (char& w) {w=o1;}
};

class XOR {
	char i1, i2, o1;
	public:
		XOR ();
		void inp (char a, char b) {i1=a; i2=b;}
		void evl ();
		void out (char& w) {w=o1;}
};
