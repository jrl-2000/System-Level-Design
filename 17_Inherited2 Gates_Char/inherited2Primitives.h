class gates {
	protected:
		char i1, i2, o1;
	public:
		void inp (char a, char b);
		void inp (char a);
		void out (char& w) {w=o1;}
		void evl() {o1=this->i1;}
};

class AND: public gates {
	public:
		AND (); // constructor
		void evl ();
};

class OR : public gates {
	public:
		OR (); // constructor
		void evl ();
};

class NOT : public gates {
	public:
		NOT ();
		void evl ();
};

class buf : public gates {
	public:
		buf () {o1='X';}
};

class XOR : public gates {
	public:
		XOR ();
		void evl ();
};
